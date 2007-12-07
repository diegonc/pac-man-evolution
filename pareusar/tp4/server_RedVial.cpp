#include "server_Dijkstra.h"
#include "server_Arco.h"
#include "server_Anden.h"
#include "server_Nodo.h"
#include "server_RedVial.h"

Dijkstra* RedVial::new_resolver( ) const
{
    return new Dijkstra( grafo );
}

void RedVial::agregar_nodo( const std::string& id )
{
    if( !grafo.existeVertice( id ) )
        grafo.agregarVertice( new Vertice( new Nodo( id ) ) );
}

void RedVial::agregar_anden( const std::string& id )
{
    if( !grafo.existeVertice( id ) )
        grafo.agregarVertice( new Vertice( new Anden( id ) ) );
}

void RedVial::agregar_via( const std::string& v1,
                           const std::string& v2,
                           const std::string& aId,
                           float peso )
{
    grafo.agregarArco( v1, v2, new Arco( aId, peso ) );
    grafo.agregarArco( v2, v1, new Arco( aId, peso ) );
}

Parada* RedVial::obtener_parada( const std::string& id ) const
{
    Vertice* v = grafo.obtenerVertice( id );
    return v->obtener_dato();
}
