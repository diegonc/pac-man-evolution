//Header
#ifndef Bonus_h_
#define Bonus_h_

//Incluyo las librerias necesarias
#include "modificador.h"

/* CLASE BONUS: Clase que representa un bonus. Desciende de modificador. Ocupa un casillero. */

class Bonus : public Modificador {

	public:

	/* Constructor: Inicializa un bonus en una posicion determinada. */
	Bonus (int pos_x, int pos_y);
	
	/* Get Tipo: Devuelve el tipo del elemento */
	virtual TipoElem get_tipo();
	
	/* Get Ruta Imagen: Devuelve una cadena con la ruta donde se encuentra la imagen que representa al elemento */
	virtual char* get_ruta_imagen();

};

#endif
