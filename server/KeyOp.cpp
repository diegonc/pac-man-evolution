#include "KeyOp.h"
#include "ModeloServidor.h"
#include "../common/smart_pointer.h"
#include "Direccion.h"
#include "Jugador.h"

const int KeyOp::arriba 	= 	0;
const int KeyOp::abajo  	= 	1;
const int KeyOp::derecha	= 	3;
const int KeyOp::izquierda	= 	2;  

KeyOp::KeyOp(int flecha,int id ){
	this->flecha = flecha;
	this->id = id;
}

void KeyOp::ejecutar(ModeloServidor &modelo)
{
	//obtiene el jugador
	S_ptr<Jugador> jugador = modelo.get_jugador(this->id);
	//combina la direccion
	jugador->get_direccion().combinar(flecha);
}


void KeyOp::set_id(int identifJugador)
{
	id=identifJugador;
}
