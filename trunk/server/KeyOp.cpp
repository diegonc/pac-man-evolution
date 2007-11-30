#include "KeyOp.h"
#include "ModeloServidor.h"
#include "../common/smart_pointer.h"
#include "Direccion.h"
#include "Jugador.h"

/**
 *  La ejecucion de la operacion lleva a cabo los siguientes pasos:
 *    -# Obtiene jugador segun id.
 *    -# Obtiene su direccion.
 *    -# Calcula la nueva direccion.
 *    -# Mueve el personaje.
 */
void KeyOp::ejecutar(ModeloServidor &modelo)
{
	//std::cout << "Pulso la tecla " << this->flecha << "\n";
	S_ptr<Jugador> jugador = modelo.get_jugador(this->id);
	//std::cout << jugador->get_direccion() <<" -->";
	jugador->get_direccion().combinar(flecha);
	//std::cout << jugador->get_direccion() <<"\n";
}
