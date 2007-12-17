#include <server/PaqueteStop.h>

namespace{
	const char ID = 3;
}

const char PaqueteStop::pacman_gano = 0;
const char PaqueteStop::pacman_comido = 1;
const char PaqueteStop::pacman_desconecto = 2;
const char PaqueteStop::cant_insuficiente = 3;
const char PaqueteStop::termino_juego = 4;

PaqueteStop::PaqueteStop() : Paquete( ID ) { }

PaqueteStop::PaqueteStop( const char razon, int puntaje ) : Paquete( ID )
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
