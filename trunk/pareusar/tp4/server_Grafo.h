#ifndef __Grafo_H__
#define __Grafo_H__

#include <map>
#include <list>
#include <cassert>
#include <stdexcept>

#ifdef DECLARED_GRAFO
/* Si se ha declarado en forma adelantada, no redefine el argumento opcional. */
template <class TVertice, class TArco, class TId>
#else
template <class TVertice, class TArco, class TId=int>
#endif
class Grafo
{
    private:
        typedef std::map<TId,TVertice> vmap;
        vmap vertices;

        class QuitarAristaSiDestinoEs {
            TVertice destino;

            public:
            QuitarAristaSiDestinoEs( TVertice v ) : destino( v ) { }

            void operator()( TArco a )
            {
                if( a->getDestino()->getId() == destino->getId() )
                    a->getOrigen()->quitarArco( a );
            }

            void operator()( TVertice v )
            {
                v->foreach_arista( *this );
            }
        };

        class Quitar {
            public:
            void operator()( TArco a )
            {
                a->getOrigen()->quitarArco( a );
            }

            void operator()( TVertice v )
            {
                v->foreach_arista( *this );
                delete v;
            }
        };

    public:
        ~Grafo()
        {
            foreach_vertice( Quitar() );
        }

        void agregarVertice( TVertice vert );

        void agregarArco( TId idOrigen, TId idDestino, TArco arco );

        bool existeVertice( TId id ) const
        {
            return ( vertices.find( id ) != vertices.end() );
        }

        TVertice obtenerVertice( TId id ) const throw( std::runtime_error );

        void quitarVertice( TId id );

        bool estaVacio() const
        {
            return vertices.empty();
        }

        template<class Functor>
        Functor foreach_vertice( Functor fun ) const;

        template<class Contenedor, class Functor>
        Functor foreach_vertice_in( Contenedor& con, Functor fun ) const;
};

template <class TVertice, class TArco, class TId>
void Grafo<TVertice,TArco,TId>::agregarVertice( TVertice vert )
{
    TId vid = vert->getId();

    assert( vertices.find( vid ) == vertices.end() );

    vertices[vid] = vert;
}

template <class TVertice, class TArco, class TId>
void Grafo<TVertice,TArco,TId>::agregarArco( TId idOrigen, TId idDestino, TArco arco )
{
    TVertice orig = obtenerVertice( idOrigen );
    TVertice destino = obtenerVertice( idDestino );

    arco->setOrigen( orig );
    arco->setDestino( destino );
    orig->agregarArco( arco );
}

template <class TVertice, class TArco, class TId>
TVertice Grafo<TVertice,TArco,TId>::obtenerVertice( TId id ) const throw( std::runtime_error )
{
    typename vmap::const_iterator it = vertices.find( id );
    if( it  == vertices.end() )
        throw std::runtime_error( "Vertice inexistente: " + id );

    return (*it).second;
}

template <class TVertice, class TArco, class TId>
void Grafo<TVertice,TArco,TId>::quitarVertice( TId id )
{
    typename vmap::iterator i = vertices.find( id );
    if( i != vertices.end() ) {
        (*i).second->foreach_arista( Quitar() );
        foreach_vertice( QuitarAristaSiDestinoEs( (*i).second ) );
        vertices.erase(i);
    }
}


template <class TVertice, class TArco, class TId>
template<class Functor>
Functor Grafo<TVertice,TArco,TId>::foreach_vertice( Functor fun ) const
{
    typename vmap::const_iterator it = vertices.begin();
    while( it != vertices.end() )
        fun( (*it++).second );

    return fun;
}

template <class TVertice, class TArco, class TId>
template<class Contenedor, class Functor>
Functor Grafo<TVertice,TArco,TId>::foreach_vertice_in( Contenedor& con, Functor fun ) const
{
    typename Contenedor::const_iterator it = con.begin();
    while( it != con.end() )
        if( existeVertice( *it ) )
            fun( obtenerVertice(*it++) );

    return fun;
}

#endif // __Grafo_H__
