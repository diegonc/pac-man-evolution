//Header
#ifndef Cruce_h_
#define Cruce_h_

//Incluyo las librerias necesarias
#include "estructural.h"
#include "punto.h"

/* CLASE CRUCE: Clase que representa una una doble bifurcacion o cruce. Hereda de Estructural. */

class Cruce : public Estructural {

	public:

	/* Constructor: Inicializa un cruce con las posiciones pasadas por parametros. */
	Cruce (int pos_x, int pos_y);

	/* Get Ruta Imagen: Devuelve una cadena con la ruta donde se encuentra la imagen que representa al elemento */
	virtual char* get_ruta_imagen();
		
	/* Get Tipo: Devuelve el tipo del elemento */
	virtual TipoElem get_tipo();


};

#endif
