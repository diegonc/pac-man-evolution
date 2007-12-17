#include "server_DijkstraResult.h"
#include "server_Vertice.h"

void DijkstraResult::setDistancia( Vertice* v, float d )
{
    ResultData r = res[ v->getId() ];
    r.distancia = d;
    res[ v->getId() ] = r;
}

void DijkstraResult::setAnterior( Vertice* v, Vertice* a )
{
    ResultData r = res[ v->getId() ];
    r.anterior = a;
    res[ v->getId() ] = r;
}

float DijkstraResult::getDistancia( const std::string& id ) const
{
    std::map<std::string,ResultData>::const_iterator it = res.find( id );
    if( it != res.end() )
        return it->second.distancia;
    else
        return DijkstraResult::Infinito();
}

float DijkstraResult::getDistancia( Vertice* v ) const
{
    return getDistancia( v->getId() );
}

Vertice* DijkstraResult::getAnterior( const std::string& id ) const
{
    std::map<std::string,ResultData>::const_iterator it = res.find( id );
    if( it != res.end() )
        return it->second.anterior;
    else
        return DijkstraResult::Inexistente();
}

Vertice* DijkstraResult::getAnterior( Vertice* v ) const
{
    return getAnterior( v->getId() );
}

bool DijkstraResult::existe_anterior( const std::string& id ) const
{
    return ( getAnterior( id ) != DijkstraResult::Inexistente() );
}
