#ifndef __Dijkstra_H__
#define __Dijkstra_H__

#define NEEDS_GRAFO
#define NEEDS_VETRICE
#define NEEDS_ARCO
#include "server_Forwards.h"

#include "server_DijkstraResult.h"
#include "server_PriorityQueue.h"
#include <string>

class Dijkstra
{
    private:
        typedef PriorityQueue<Vertice*, DijkstraResult::DistanceComparer> Queue;

        const Grafo<Vertice*,Arco*, std::string>& grafo;
        Queue queue;
        std::string fuente;

        class Desmarcador
        {
            private:
                DijkstraResult& result;

            public:
                Desmarcador( DijkstraResult& r ) : result( r ) { }
                void operator()( Vertice* v );
        };

        class Marcador
        {
            private:
                DijkstraResult& result;

            public:
                Marcador( DijkstraResult& r ) : result( r ) { }
                void operator()( Arco* arco );
        };
    public:
        Dijkstra( const Grafo<Vertice*,Arco*,std::string>& grafo );
        const std::string& getFuente( ) const { return fuente; }
        void setFuente( const std::string& id ) { fuente = id; }
        DijkstraResult solve( );
};

#endif // __Dijkstra_H__
