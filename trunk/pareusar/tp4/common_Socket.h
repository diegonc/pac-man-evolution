#ifndef __SOCKET_H__
#define __SOCKET_H__

#include <sys/socket.h>
#include <netdb.h> // para sockaddr_in, gethostbyname
#include <unistd.h> // para close()
#include <arpa/inet.h> // htonl htons ntohl ntohs
#include <vector>
#include "common_Errores.h"

class Socket
{
    public:
        enum Tipo {
            TCP = SOCK_STREAM,
            UDP = SOCK_DGRAM
        };

        class ConnectionClosed
        {
            /*
             * Clase utilizada como excepcion cuando la conexión ha sido
             * cerrada correctamente por el equipo remoto pero se intenta leer
             * o escribir en el socket.
             */
        };

        static uint32_t hton(uint32_t hostlong) { return ::htonl( hostlong ); }
        static uint16_t hton(uint16_t hostshort) { return ::htons( hostshort ); }
        static uint32_t ntoh(uint32_t netlong) { return ::ntohl( netlong ); }
        static uint16_t ntoh(uint16_t netshort) { return ::ntohs( netshort ); }

    private:
        int fd;
        Tipo tipo;
        unsigned int intentos; // Numero de veces que se reintenta la operacion
                               // si es interrumpida.

        Socket( int fd, Tipo tipo ) : fd( fd ), tipo( tipo ), intentos(1) { }

    public:
        Socket( Tipo tipo );

        ~Socket();

        void bind( int port );

        void listen();

        void connect( const std::string& ip, int port );

        /* Encapsulan las funciones en forma casi directa send y recv,
         * transformando codigos de error en excepciones. Retornan el numero de
         * bytes enviados o recividos.
         */
        int read( void* buffer, unsigned int size );
        int write( void* buffer, unsigned int size );

        /* Los siguientes tres metodos envian o reciben un dato en su totalidad
         * salvo que se encuentre alguna condicion excepcional.
         */
        template<class T>
        void write( T t );

        void write( const std::string& data );

        template<class T>
        void read( T& t );

        Socket* accept();

        void set_intentos( unsigned int i ) { intentos = i; }

        unsigned int get_intentos() const { return intentos; }

        void set_reuse_addr( bool b );
};

template<class T>
void Socket::write( T t )
{
    unsigned int intentos = this->intentos; // numero de intentos de envio restantes
    int r = 0, l=sizeof(T); // r bytes enviados, l bytes restantes
    char* buffer = (char*) &t;

    while( l != 0 ) {
        try {
            r = write( buffer, l );
            l -= r;
            buffer += r;
        } catch( Error::SystemError e ) {
            // Si se interumpio la llamada, intenta completar el envio
            // correctamente un numero 'intentos' de veces.
            if( !e.interrumpido() || ( intentos == 0 ) )
                throw;
            // Interrumpido y aun quedan intentos
            intentos--;
        }
    }
}

template<class T>
void Socket::read( T& t )
{
    unsigned int intentos = this->intentos; // numero de intentos de recepcion restantes
    int r = 0, l=sizeof(T); // r bytes recibidos, l bytes restantes
    char* buffer = (char*) &t;

    while( l != 0 ) {
        try {
            r = read( buffer, l );
            l -= r;
            buffer += r;
        } catch( Error::SystemError e ) {
            // Si se interumpio la llamada, intenta completar el envio
            // correctamente un numero 'intentos' de veces.
            if( !e.interrumpido() || ( intentos == 0 ) )
                throw;
            // Interrumpido y aun quedan intentos
            intentos--;
        }
    }
}

#endif /* __SOCKET_H__ */
