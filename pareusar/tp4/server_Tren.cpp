#include "server_Log.h"
#include "server_LogEntry.h"
#include "server_Tren.h"
#include "server_RedVial.h"
#include "server_Dijkstra.h"
#include "server_DijkstraResult.h"
#include "server_EventPool.h"
#include "server_Parada.h"
#include "common_Time.h"
#include "common_Errores.h"
#include <iostream>
#include <sstream>

float Tren::velocidad = 25.0; /* Velocidad en km/s */

class Tren::DatoParada
{
    public:
    Parada* parada;
    float distancia;
};

void Tren::calcularDistancias()
{
    /* Calcula las distancias desde cada anden al anden anterior.
     *   1. Fuente: anden salida
     *   2. Para cada elemento en la lista de paradas
     *      2.1. Resuelve con dijkstra.
     *      2.2. Fuente: anden actual.
     *      2.3. Actualiza distancia del elemento.
     *      2.4. Inserta detrás de este todos los puntos intermedios.
     */
    dijkstra->setFuente( salida );
    std::list<DatoParada>::iterator it = paradas.begin();
    while( it != paradas.end() ) {
        DijkstraResult r = dijkstra->solve();
        DatoParada p = *it;
        dijkstra->setFuente( p.parada->getId() );
        paradas.erase( it++ );
        std::list<DatoParada>::iterator cur = it;
        while( r.existe_anterior( p.parada->getId() ) ) {
            // Guarda la distancia desde el nodo anterior al actual.
            Vertice* anterior = r.getAnterior( p.parada->getId() );
            // distancia hasta nodo actual
            p.distancia = r.getDistancia( p.parada->getId() );
            // distancia desde nodo anterior
            p.distancia -= r.getDistancia( anterior );
            cur = paradas.insert( cur, p );
            p.parada = anterior->obtener_dato();
        }
    }
}

Tren::Tren( const std::vector<std::string>& itinerario, const RedVial& rv)
{
    dijkstra = rv.new_resolver();
    id = itinerario[0];
    salida = itinerario[1];
    for( unsigned int i=2; i< itinerario.size(); i++ ) {
        DatoParada p;
        p.parada = rv.obtener_parada( itinerario[i] );
        p.distancia = 0;
        paradas.push_back( p );
    }
    trenListo = EventPool::getInstance().crear_evento( "tren-listo" );
}

Tren::~Tren()
{
    delete dijkstra;
}

void Tren::transitarVia( const std::list<DatoParada>::iterator& i )
{
    float tiempo = (*i).distancia / velocidad;
    sleep( tiempo );
}

void Tren::tomarAnden( const std::list<DatoParada>::iterator& i )
{
    Parada* parada = (*i).parada;

    // Ocupa parada
    parada->ocupar( this, &en_parada );

    // Descarga de pasajeros
    parada->descargar();
}

void* Tren::run()
{
    try {
        // Calcula las distancias de su itinerario.
        calcularDistancias();

        std::list<DatoParada>::iterator it = paradas.begin();

        // Notifica que esta listo para partir.
        trenListo->activar();

        // Aguarda notificación de inicio de simulación.
        EventPool::getInstance().esperar( "simulacion-inicio" );

        Log::getInstance().add( LogEntry::crear_sale( id, salida ) );

        while( it != paradas.end() ) {
            transitarVia( it );
            tomarAnden( it );
            ++it;
        }

        Log::getInstance().add( LogEntry::crear_termina( id ) );
    } catch( std::runtime_error e ) {
        std::cerr << "Tren ( " << id << " ) no puede continuar: ";
        std::cerr << e.what() << std::endl;
    }
       return 0;
}

const std::string& Tren::getId() const
{
    return id;
}
