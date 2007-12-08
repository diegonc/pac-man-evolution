#include "Cliente.h"

#include "InputBitStream.h"
#include "SocketReader.h"

Cliente::Cliente(Tipo_Id id, Socket_Cliente * socket)
{
	this->id = id;
	this->socket = socket;
	// modelo->agregar_jugador( Tipo_Jugador( new Jugador(id) ) );
}

void Cliente::run()
{

}

Cliente::~Cliente()
{
	if( socket )
		delete socket;
}

void Cliente::enviar_mensaje( S_ptr<Paquete> paquete )
{
	OutputBitStream obs;

	paquete->serialize( obs );

	const unsigned char* raw = obs.get_data();

	socket->escribir( raw, obs.get_size() );
}

S_ptr<Paquete> Cliente::recibir_mensaje()
{
	SocketReader sr( *socket );
	InputBitStream bs( sr );
	Paquete* p = 0;

	// Lectura de encabezado
	int version = bs.read( 2 );
	if( version == 0 ) {
		// Lectura de tipo de paquete.
		int tipo = bs.read( 3 );
		p = Paquete::crear( tipo );
		p->deserialize( bs );
	}
	return S_ptr<Paquete>( p );
}
