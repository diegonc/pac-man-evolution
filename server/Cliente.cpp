#include "Cliente.h"

#include "InputBitStream.h"
#include "SocketReader.h"

void Cliente::run()
{

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
