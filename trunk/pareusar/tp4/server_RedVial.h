#ifndef __REDVIAL_H__
#define __REDVIAL_H__

#define NEEDS_PARADA
#define NEEDS_DIJKSTRA
#include "server_Forwards.h"

#include "server_Vertice.h"
#include "server_Grafo.h"
#include "server_Arco.h"
#include <iostream>
#include <string>

class RedVial
{
    private:
        Grafo<Vertice*, Arco*, std::string> grafo;

        template<class Functor>
        class to_parada
        {
            Functor f;
            public:
            to_parada( Functor f ) : f( f ) { }
            void operator()( Vertice* v )
            {
                f( v->obtener_dato() );
            }
        };

    public:
        Dijkstra* new_resolver( ) const;

        void agregar_nodo( const std::string& id );

        void agregar_anden( const std::string& id );

        void agregar_via( const std::string& v1,
                          const std::string& v2,
                          const std::string& aId,
                          float peso );

        Parada* obtener_parada( const std::string& id ) const;

        template<class Functor>
        Functor foreach_parada( Functor fun )
        {
            grafo.foreach_vertice( to_parada<Functor>( fun ) );
            return fun;
        }
};

#endif /* __REDVIAL_H__ */
