//Header
#ifndef Pas_Horiz_h_
#define Pas_Horiz_h_

//Incluyo las librerias necesarias
#include "estructural.h"
#include "punto.h"

/* CLASE PASILLO HORIZ: Clase que representa un pasillo horizontal. Desciende de estructural. Se conecta por las puntas.
   La orientacion es ESTE por defecto. */

class PasilloHoriz : public Estructural {

	public:

	/* Constructor: Inicializa un pasillo horizontal con las coords pasadas por parametro. */
	PasilloHoriz (int pos_x, int pos_y);
	
	/* Get Tipo: Devuelve el tipo del elemento */
	virtual TipoElem get_tipo();

	/* Get Ruta Imagen: Devuelve una cadena con la ruta donde se encuentra la imagen que representa al elemento */
	virtual char* get_ruta_imagen();

	/* ///////////////TEMPORAL/////////////// */
	virtual char* toString();

};

#endif
