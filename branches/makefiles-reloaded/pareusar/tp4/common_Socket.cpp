#include "common_Socket.h"
#include "common_Time.h"
#include <string>
#include <cstring>
#include <algorithm>
#include <iostream>

Socket::Socket( Tipo tipo )
{
    intentos = 1;
    this->tipo = tipo;
    fd = socket( AF_INET, tipo, 0 );
    if( fd == -1 )
        throw Error::SystemError();
}

Socket::~Socket()
{
    close( fd );
}

void Socket::bind( int port )
{
    struct sockaddr_in addr;

    memset( &addr, 0, sizeof( sockaddr_in ) );
    addr.sin_family = AF_INET;
    addr.sin_port = htons( port );
    addr.sin_addr.s_addr = INADDR_ANY;

    if( ::bind( fd, (sockaddr*)&addr, sizeof( sockaddr ) ) == -1 )
        throw Error::SystemError();
}

void Socket::listen( )
{
    if( tipo == TCP ) {
        if( ::listen( fd, 5 ) == -1 )
            throw Error::SystemError();
    }
}

Socket* Socket::accept()
{
    sockaddr_in addr;
    socklen_t addr_len = sizeof( sockaddr_in );

    int result = ::accept( fd, (sockaddr*)&addr, &addr_len );
    if( result > -1 )
        return new Socket( result, tipo );
    else
        throw Error::SystemError( );
}

void Socket::write( const std::string& data )
{
    int intentos = 1; // numero de intentos de envio restantes
    int r = 0, l=data.size(); // r bytes enviados, l bytes restantes
    const char* buffer = data.c_str();

    while( l != 0 ) {
        r = ::send( fd, buffer, l, 0 );
        if( r == -1 ) {
            // Si se interumpio la llamada, reintenta, N=1 veces,
            // completar el envio correctamente
            Error::SystemError e;
            if( !e.interrumpido() || ( intentos == 0 ) ) {
                // Verificar que no se haya cerrado la conexion.
                if( errno == ECONNRESET )
                    throw ConnectionClosed();
                else
                    throw e;
            }
            // Interrumpido y aun quedan intentos
            intentos--;
        } else {
            // Se enviaron correctamente r bytes
            l -= r;
            buffer += r;
        }
    }
}

void Socket::connect( const std::string& ip, int port )
{
    struct sockaddr_in addr;
    struct hostent *he;

    he = gethostbyname( ip.c_str() );

    memset( &addr, 0, sizeof( sockaddr_in ) );
    addr.sin_family = AF_INET;
    addr.sin_port = htons( port );
    addr.sin_addr = *((struct in_addr *)he->h_addr);

    if( ::connect( fd, (sockaddr*)&addr, sizeof(sockaddr_in) ) == -1 )
        throw Error::SystemError( );
}

int Socket::read( void* buffer, unsigned int size )
{
    int r = ::recv( fd, buffer, size, 0 );
    if( r == 0 )
        throw ConnectionClosed();
    else if( r == -1 )
        throw Error::SystemError();

    return r;
}

int Socket::write( void* buffer, unsigned int size )
{
    int r = ::send( fd, buffer, size, 0 );
    if( r == -1 )
        if( errno == ECONNRESET )
            throw ConnectionClosed();
        else
            throw Error::SystemError();

    return r;
}

void Socket::set_reuse_addr( bool b )
{
    int reuse = ( b ? 1 : 0 );
    setsockopt( fd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(int) );
}
