#include "KeyOp.h"
#include "MundoBasicImp.h"
#include "Mapa.h"

void KeyOp::ejecutar()
{
	/* TODO: Si bien se usa la interfaz se debe conocer la implementacion
	 * particular.
	 */
	Mundo& mundo = MundoBasicImp::get_instance();
	Mapa& mapa = mundo.get_mapa_activo();
	/* Por ahora:
	 *   1. Pide personaje segun id.
	 *   2. Obtiene su direccion.
	 *   3. Calcula la nueva direccion.
	 *   4. Mueve el personaje.
	 */
	Personaje& p = mapa.get_personaje( id );
	Mapa::Direccion d = p.get_direccion();

	d = (d + flecha) % 4;

	mapa.mover( id, d );
}
