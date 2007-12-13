#include "common_StringUtil.h"

const char* StringUtil::buscarToken( const char* str, char token )
{
    while( *str && ( *str != token ) ) str++;
    return str;
}

const char* StringUtil::saltearToken( const char* str, char token )
{
    if( *str && ( *str == token ) )
        str++;
    return str;
}

void StringUtil::nuevaPieza( std::vector<std::string>& destino,
                        const char* inicio,
                        const char* fin )
{
    // salteo espacios en blanco al comienzo
    while( (inicio < fin) && ( *inicio == ' ' ) ) inicio++;
    // salteo espacios en blanco al final
    while( (inicio < fin) && ( *(fin-1) == ' ' ) ) fin--;

    destino.push_back( std::string( inicio, fin-inicio ) );
}

std::vector<std::string> StringUtil::explode( const char* str, char token )
{
    std::vector<std::string> piezas;
    const char* inicio;

    if( str ) {
        while( *str ) {
            inicio = str;
            str = buscarToken( str, token );
            nuevaPieza( piezas, inicio, str);
            str = saltearToken( str, token );
        }
        if( *(str-1) == token )
            nuevaPieza( piezas, str, str );
    }

    return piezas;
}
