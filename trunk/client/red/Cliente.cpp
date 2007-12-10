#include "Cliente.h"
#include <iostream>
#include "server/OutputBitStream.h"
#include "server/InputBitStream.h"
#include "server/SocketReader.h"
#include "server/Paquete.h"

#define _VERSION_ACEPTADA 0

Cliente::Cliente( const std::string& ip, short port )
{
	this->ip = ip;
	this->port = port;
}

void Cliente::enviar_mensaje( S_ptr<Paquete> paquete )
{
	OutputBitStream obs;
	
	paquete->serialize( obs );
	const unsigned char* raw = obs.get_data();
	
	socket.escribir( raw, obs.get_size() );
}

S_ptr<Paquete> Cliente::recibir_mensaje()
{
	SocketReader sr( socket );
	InputBitStream bs( sr );
	Paquete* p = 0;
	// Lectura de encabezado
	int version = bs.read( 2 );
	if( version == _VERSION_ACEPTADA ) {
		// Lectura de tipo de paquete.
		int tipo = bs.read( 3 );
		p = Paquete::crear( tipo );
		if( p/*.es_nulo()*/ ){
			p->deserialize( bs );
		}
	}
	return S_ptr<Paquete>( p );
}

void Cliente::run()
{
    try {
        socket.conectar( ip, port );
	while( true ) {
		S_ptr<Paquete> p = recibir_mensaje();
	}
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
