#ifndef __DIJKSTRARESULT_H__
#define __DIJKSTRARESULT_H__

#define NEEDS_VERTICE
#include "server_Vertice.h"

#include <map>
#include <limits>
#include <string>

class DijkstraResult
{
    private:
        struct ResultData
        {
            float distancia;
            Vertice* anterior;
        };

        std::map<std::string,ResultData> res;

    public:
        static float Infinito(){return std::numeric_limits<float>::infinity();}

        static Vertice* Inexistente(){ return NULL; }

        void setDistancia( Vertice* v, float d );

        void setAnterior( Vertice* v, Vertice* a );

        float getDistancia( const std::string& id ) const;

        float getDistancia( Vertice* v ) const;

        Vertice* getAnterior( const std::string& id ) const;

        Vertice* getAnterior( Vertice* v ) const;

        bool existe_anterior( const std::string& id ) const;

    public:
        class DistanceComparer
        {
            private:
                DijkstraResult& r;

            public:
                DistanceComparer( DijkstraResult& r ) : r( r ) { }
                bool operator()( Vertice* a, Vertice* b )
                {
                    if( r.getDistancia( a ) > r.getDistancia( b ) )
                        return true;

                    return false;
                }
        };
};

#endif /* __DIJKSTRARESULT_H__ */
