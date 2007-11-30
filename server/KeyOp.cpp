#include "KeyOp.h"
#include "ModeloServidor.h"
#include "../common/smart_pointer.h"
#include "Direccion.h"
#include "Jugador.h"

const int arriba 	= 	0;
const int abajo  	= 	2;
const int derecha	= 	3;
const int izquierda = 	4;

void KeyOp::ejecutar(ModeloServidor &modelo)
{
	//std::cout << "Pulso la tecla " << this->flecha << "\n";
	S_ptr<Jugador> jugador = modelo.get_jugador(this->id);
	//std::cout << jugador->get_direccion() <<" -->";
	jugador->get_direccion().combinar(flecha);
	//std::cout << jugador->get_direccion() <<"\n";
}
