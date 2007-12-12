#include "server_Parser.h"
#include "server_RedVial.h"
#include "common_StringUtil.h"
#include "server_Tren.h"
#include <iostream>

void Parser::agregar_vertice( const std::string& id, const std::string& tipo )
{
    if( tipo == "NODO" )
        red.agregar_nodo( id );
    else if( tipo == "ANDEN" )
        red.agregar_anden( id );
    else
        throw InvalidFormat("Tipo de vertice invalido." );
}

void Parser::agregar_arista( const std::string& vId1,
                             const std::string& vId2,
                             const std::string& aId,
                             const std::string& tipo,
                             float peso )
{
    if( tipo == "VIA" ) {
        red.agregar_via( vId1, vId2, aId, peso );
    }
    else
        throw InvalidFormat( "Tipo de via invalido." );
}

void Parser::processLine( std::string& line )
{
    std::vector<std::string> piezas = StringUtil::explode( line.c_str(), ',' );
    std::string vId1, vId2;
    std::string vTipo;

    // Agrega vertice 1
    StringUtil::convertir( piezas[3], vId1 );
    StringUtil::convertir( piezas[4], vTipo );
    agregar_vertice( vId1, vTipo );

    // Agrega vertice 2
    StringUtil::convertir( piezas[5], vId2 );
    StringUtil::convertir( piezas[6], vTipo );
    agregar_vertice( vId2, vTipo );

    // v1 <--> v2
    std::string aId;
    std::string aTipo;
    float aPeso;
    StringUtil::convertir( piezas[0], aId );
    StringUtil::convertir( piezas[1], aPeso );
    StringUtil::convertir( piezas[2], aTipo );
    agregar_arista( vId1, vId2, aId, aTipo, aPeso );
}

Parser::Parser( RedVial& r ) : red( r )
{

}

void Parser::parseConfig( std::istream& fd )
{
    std::string line;

    while( getline( fd, line ) )
        processLine( line );
}

std::vector<Tren*> Parser::parseItinerario( std::istream& fd )
{
    std::string line;
    std::vector<Tren*> tmp;

    while( getline( fd, line ) ) {
        Tren* t = new Tren( StringUtil::explode(line.c_str(),','), red );
        tmp.push_back( t );
    }
    return tmp;
}
