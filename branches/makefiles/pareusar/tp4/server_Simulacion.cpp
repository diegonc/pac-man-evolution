#include "server_Parser.h"
#include "server_Log.h"
#include "server_EventPool.h"
#include "server_Tren.h"
#include "server_Simulacion.h"
#include "common_StringUtil.h"
#include "common_Errores.h"

Simulacion::Simulacion( std::istream& fd_red, std::istream& fd_it )
    : p( red ), fd_red( fd_red ), fd_it( fd_it )
{
}

Simulacion::~Simulacion( )
{
    std::list<Tren*>::iterator it = trenes.begin();
    while( it != trenes.end() )
        delete *it++;
}

void Simulacion::inicializar_eventos()
{
    EventPool& pool = EventPool::getInstance();

    fin = pool.crear_evento( "simulacion-fin" );
    inicio = pool.crear_evento( "simulacion-inicio" );
}

void Simulacion::cargar_red()
{
    p.parseConfig( fd_red );
}

void Simulacion::cargar_itinerario()
{
    std::vector<Tren*> t = p.parseItinerario( fd_it );
    trenes.insert( trenes.begin(), t.begin(), t.end() );
}

void Simulacion::comenzar()
{
    // Lanza los trenes.
    std::list<Tren*>::iterator it = trenes.begin();
    while( it != trenes.end() )
        (*it++)->start();

    // Espera a los trenes.
    EventPool::getInstance().esperar( "tren-listo" );
    // Establece tiempo base.
    Log::getInstance().set_start_time( Time::now() );
    // Notifica a los hilos el comienzo de la simulacion.
    inicio->activar();
    // Cede el tiempo para que puedan comenzar de inmediato.
    Thread::yield();
}

void Simulacion::aguardar()
{
    // Espera hilo de trenes
    std::list<Tren*>::iterator it = trenes.begin();
    while( it != trenes.end() )
        (*it++)->join();
    // Activa evento fin de simulacion
    fin->activar();
    // Produce una entrada de log dummy para desbloquear
    Log::getInstance().add( LogEntry::crear_dummy() );
}

int Simulacion::run( )
{
    try {
        inicializar_eventos();
        cargar_red();
        cargar_itinerario();
        comenzar();
        aguardar();
    } catch( std::runtime_error e ) {
        std::cerr << e.what() << std::endl;
        return Error::OTRO;
    }
    return Error::OK;
}
