#include "KeyOp.h"
#include "MundoBasicImp.h"
#include "Mapa.h"
#include "Direccion.h"
#include "Personaje.h"
#include "../common/smart_pointer.h"

void KeyOp::ejecutar()
{
	/* TODO: Si bien se usa la interfaz se debe conocer la implementacion
	 * particular.
	 */
	S_ptr<Mundo> mundo = MundoBasicImp::get_instancia();
	Mapa& mapa = mundo->get_mapa_activo();
	/* Por ahora:
	 *   1. Pide personaje segun id.
	 *   2. Obtiene su direccion.
	 *   3. Calcula la nueva direccion.
	 *   4. Mueve el personaje.
	 */
	Personaje& p = mapa.get_personaje( id );
	Direccion d = p.get_direccion().combinar( flecha );
	mapa.mover( id, d );
}
