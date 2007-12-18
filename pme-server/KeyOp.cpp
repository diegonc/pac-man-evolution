#include "KeyOp.h"

#include "../common/ModeloCommon.h"
#include "../common/smart_pointer.h"
#include "../common/Direccion.h"
#include "../common/Jugador.h"

const int KeyOp::arriba 	= 	0;
const int KeyOp::abajo  	= 	1;
const int KeyOp::derecha	= 	3;
const int KeyOp::izquierda	= 	2;  

KeyOp::KeyOp(unsigned int flecha,int id ){
	this->flecha = flecha;
	this->id = id;
}

void KeyOp::ejecutar(ModeloCommon &modelo)
{
	//obtiene el jugador
	Jugador * jugador = modelo.get_jugador(this->id);
	//combina la direccion
	jugador->get_direccion().combinar(flecha);
}


void KeyOp::set_id(unsigned int identifJugador)
{
	id=identifJugador;
}
