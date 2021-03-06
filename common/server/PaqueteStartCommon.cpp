#include <server/PaqueteStartCommon.h>

#include <server/MundoBajoNivel.h>
#include <server/PacMan.h>
#include <server/Fantasma.h>
#include <server/Personaje.h>
#include <server/Jugador.h>
#include <list>
#include <server/Jugador.h>
#include <common/smart_pointer.h>

namespace {
	const int ID = 1;
}

PaqueteStartCommon::PaqueteStartCommon() : Paquete( ID )
{
}

PaqueteStartCommon::PaqueteStartCommon(int id_cliente):Paquete( ID ){
	this->id_cliente = id_cliente;
}

void PaqueteStartCommon::serialize( OutputBitStream& bs ){
	Paquete::serialize( bs );
	bs.skip();
	
	bs.append(16,id_cliente);
}

void PaqueteStartCommon::deserialize( InputBitStream& bs ) {
	bs.skip(); // Campo auxiliar no utilizado.
	id_cliente = bs.read( 16 );
	
}
