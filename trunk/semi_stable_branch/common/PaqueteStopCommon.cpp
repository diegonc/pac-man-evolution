#include "PaqueteStopCommon.h"

namespace{
	const char ID = 3;
}

const char PaqueteStopCommon::pacman_gano = RazonPacmanGano;
const char PaqueteStopCommon::pacman_comido = RazonPacmanComido;
const char PaqueteStopCommon::pacman_desconecto = RazonPacmanDesconecto;
const char PaqueteStopCommon::cant_insuficiente = RazonCantidadInsuficiente;
const char PaqueteStopCommon::termino_juego = RazonTerminoJuego;

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

