#include "KeyOp.h"
#include "MundoBasicImp.h"
#include "Mapa.h"
#include "Direccion.h"
#include "Jugador.h"
#include "../common/smart_pointer.h"
/**
 *  La ejecucion de la operacion lleva a cabo los siguientes pasos:
 *    -# Obtiene jugador segun id.
 *    -# Obtiene su direccion.
 *    -# Calcula la nueva direccion.
 *    -# Mueve el personaje.
 */
void KeyOp::ejecutar()
{
	/* TODO: Si bien se usa la interfaz se debe conocer la implementacion
	 * particular.
	 */
	S_ptr<Mundo> mundo = MundoBasicImp::get_instancia();
	Mapa& mapa = mundo->get_mapa_activo();
	//S_ptr<Jugador> p = mapa.get_personaje( id );
	//Direccion d = p.get_direccion()->combinar( flecha );
	//mapa.mover( id, d );
}
