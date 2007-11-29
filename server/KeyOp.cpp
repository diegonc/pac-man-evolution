#include "KeyOp.h"
#include "Modelo.h"
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
void KeyOp::ejecutar(Modelo &modelo)
{
	std::cout << "Pulso la tecla " << this->id << "\n";
	S_ptr<Jugador> jugador = modelo.get_jugador(this->id);
	jugador->get_direccion().combinar(flecha);
}
