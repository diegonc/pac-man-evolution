//Header
#include "power_up.h"

/* CLASE POWER UP: Clase que representa un power up. Desciende de modificador. Ocupa un casillero. */

/* Constructor: */

PowerUp::PowerUp (int pos_x, int pos_y) : Modificador(pos_x, pos_y) {}

/* Get Tipo: */
	
TipoElem PowerUp::get_tipo(){
	return PWUP;	
}

/* Get Ruta Imagen: */

char* PowerUp::get_ruta_imagen(){
		return RUTA_POWER_UP;
}

/* ///////////////TEMPORAL/////////////// */

char* PowerUp::toString(){
	return "POWER UP";
}
