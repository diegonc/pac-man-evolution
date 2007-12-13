#include "server_Vertice.h"
#include "server_Arco.h"
#include "server_Grafo.h"
#include "server_Dijkstra.h"
#include <assert.h>

Dijkstra::Dijkstra( const Grafo<Vertice*,Arco*,std::string>& grafo )
    : grafo( grafo )
{

}

void Dijkstra::Desmarcador::operator()( Vertice* v )
{
    result.setDistancia( v, DijkstraResult::Infinito() );
    result.setAnterior( v, DijkstraResult::Inexistente() );
}

void Dijkstra::Marcador::operator()( Arco* arco )
{
    float dist;
    float dist_inicial;

    dist_inicial = dist = result.getDistancia( arco->getOrigen() );
    dist += arco->getPeso();
    if( dist < dist_inicial )
        dist = dist_inicial;

    if( dist < result.getDistancia( arco->getDestino() ) ) {
        result.setDistancia( arco->getDestino(), dist );
        result.setAnterior( arco->getDestino(), arco->getOrigen() );
    }
}

DijkstraResult Dijkstra::solve( )
{
    DijkstraResult r;
    DijkstraResult::DistanceComparer comp( r );

    grafo.foreach_vertice( Dijkstra::Desmarcador( r ) );
    r.setDistancia( grafo.obtenerVertice( fuente ), 0 );

    queue.clear();
    grafo.foreach_vertice( Queue::Filler( queue, comp ) );

    while( !queue.empty() ) {
        Vertice* u = queue.pop();
        u->foreach_arista( Dijkstra::Marcador( r ) );
        queue.sort( comp );
    }

    return r;
}
