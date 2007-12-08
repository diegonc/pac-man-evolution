#include "Cliente.h"
#include <iostream>

Cliente::Cliente( const std::string& ip, short port )
{
	this->ip = ip;
	this->port = port;
}

void Cliente::run()
{
    try {
	Socket_Cliente sock;
        sock.conectar( ip, port );

	//TODO: recibir paquetes.
/*
    } catch( Socket::ConnectionClosed e ) {

    } catch( Error::SystemError e ) {
        if( !e.interrumpido() ){
            // Se no ha sido interrumpido, muestra error.
            std::cerr << e.what() << std::endl;
        }
        error = Error::OTRO;
    }
*/  }catch( std::runtime_error e ) {
    }
}
