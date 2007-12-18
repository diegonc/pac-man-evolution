#include <server/PaqueteStopCommon.h>

namespace{
	const char ID = 3;
}

const char PaqueteStopCommon::pacman_gano = 0;
const char PaqueteStopCommon::pacman_comido = 1;
const char PaqueteStopCommon::pacman_desconecto = 2;
const char PaqueteStopCommon::cant_insuficiente = 3;
const char PaqueteStopCommon::termino_juego = 4;

PaqueteStopCommon::PaqueteStopCommon() : Paquete( ID ) { }

PaqueteStopCommon::PaqueteStopCommon( const char razon, int puntaje ) : Paquete( ID )
{
	this->razon = razon;
	this->puntuacion = puntaje;
}

void PaqueteStopCommon::serialize( OutputBitStream& bs ){
	Paquete::serialize( bs );
	bs.append( 3, razon );
	
	bs.append( 32, puntuacion );
}

void PaqueteStopCommon::deserialize( InputBitStream& bs ) {
	razon = bs.read( 3 );
	puntuacion = bs.read( 32 );
}

