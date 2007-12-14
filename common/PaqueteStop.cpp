#include "PaqueteStop.h"

namespace{
	const char ID = 3;
}

PaqueteStop::PaqueteStop() : Paquete( ID ) { }

PaqueteStop::PaqueteStop( int razon, int puntaje ) : Paquete( ID )
{
	this->razon = razon;
	this->puntuacion = puntaje;
}

void PaqueteStop::serialize( OutputBitStream& bs ){
	Paquete::serialize( bs );
	bs.append( 3, razon );
	
	bs.append( 32, puntuacion );
}

void PaqueteStop::deserialize( InputBitStream& bs ) {
	razon = bs.read( 3 );
	puntuacion = bs.read( 32 );
}

Operacion * PaqueteStop::get_operacion(){
	throw "PaqueteStop::get_operacion: Implementacion pendiente.";
}
