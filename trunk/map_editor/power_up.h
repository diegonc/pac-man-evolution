//Header
#ifndef Power_Up_h_
#define Power_Up_h_

//Incluyo las librerias necesarias
#include "modificador.h"

/* CLASE POWER UP: Clase que representa un power up. Desciende de modificador. Ocupa un casillero. */

class PowerUp : public Modificador {

	public:

	/* Constructor: Inicializa un power up en una posicion determinada. */
	PowerUp (int pos_x, int pos_y);
	
	/* Get Ruta Imagen: Devuelve una cadena con la ruta donde se encuentra la imagen que representa al elemento */
	virtual char* get_ruta_imagen();

	/* ///////////////TEMPORAL/////////////// */
	virtual char* toString();

};

#endif
