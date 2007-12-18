//Header
#include <editor/power_up.h>

/* CLASE POWER UP: Clase que representa un power up. Desciende de modificador. Ocupa un casillero. */

/* Constructor: */

Power_Up::Power_Up (int pos_x, int pos_y) : Modificador(pos_x, pos_y) {}

/* Get Tipo: */
	
TipoElem Power_Up::get_tipo(){
	return PWUP;	
}

/* Get Ruta Imagen: */

char* Power_Up::get_ruta_imagen(){
		return RUTA_POWER_UP;
}
