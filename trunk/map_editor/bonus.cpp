//Header
#include "bonus.h"

/* CLASE BONUS: Clase que representa un bonus. Desciende de modificador. Ocupa un casillero. */

/* Constructor: */

Bonus::Bonus (int pos_x, int pos_y) : Modificador(pos_x, pos_y) {}

/* Get Tipo: */
	
TipoElem Bonus::get_tipo(){
	return BONUS;	
}

/* Get Ruta Imagen: */

char* Bonus::get_ruta_imagen(){
		return RUTA_BONUS;
}

/* ///////////////TEMPORAL/////////////// */

char* Bonus::toString(){
	return "BONUS";
}
