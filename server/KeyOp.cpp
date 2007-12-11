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
	std::cout << "key op init" << std::endl << std::flush;
	//obtiene el jugador
	S_ptr<Jugador> jugador = modelo.get_jugador(this->id);
	//combina la direccion
	std::cout << jugador->get_direccion() << "---->";
	jugador->get_direccion().combinar(flecha);
	std::cout << jugador->get_direccion() << "\n";
	std::cout << "key op fin" << std::endl << std::flush;
}


void KeyOp::set_id(int identifJugador)
{
	id=identifJugador;
}
