#include "KeyOp.h"
#include "ModeloServidor.h"
#include "../common/smart_pointer.h"
#include "Direccion.h"
#include "Jugador.h"

const int arriba 	= 	0;
const int abajo  	= 	2;
const int derecha	= 	3;
const int izquierda = 	4;  //estan mal.. => mirar las del .h

void KeyOp::ejecutar(ModeloServidor &modelo)
{
	if (id==-1){
		std::cerr<< "falta obtener el id de quien envia el paquete \n\n";
		throw "error";
	}
	//obtiene el jugador
	S_ptr<Jugador> jugador = modelo.get_jugador(this->id);
	//combina la direccion
	jugador->get_direccion().combinar(flecha);
}

void KeyOp::set_id(int identifJugador)
{
	id=identifJugador;
}

int KeyOp::get_teclaFormatoPaquete(KeyOp* Key){
	switch (Key->flecha){
		case 0: //arriba
			return 0;
		case 2: //abajo
			return 1;
		case 3: //izquierda
			return 2;
		case 1: //derecha
			return 3;
		default:
			return -1;
	}
}

int KeyOp::get_teclaFormatoOperacion(int flecha){
	switch (flecha){
		case 0: //arriba
			return 0;
		case 1: //abajo
			return 2;
		case 2: //izquierda
			return 3;
		case 3: //derecha
			return 1;
		default:
			return -1;
	}
}
