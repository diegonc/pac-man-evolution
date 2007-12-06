//Header
#ifndef Casa_Sur_h_
#define Casa_Sur_h_

//Incluyo las librerias necesarias
#include "casa_fantasmas.h"
#include "punto.h"

/* CLASE CASA SUR: Clase que representa una casa de fantasmas con orientacion SUR. Hereda de CasaFantasmas. */

class CasaSur : public CasaFantasmas {

	public:

	/* Constructor: Inicializa una casa sur con las posiciones pasadas por parametros. */
	CasaSur (int pos_x, int pos_y);

	/* Get Ruta Imagen: Devuelve una cadena con la ruta donde se encuentra la imagen que representa al elemento */
	virtual char* get_ruta_imagen();

	/* ///////////////TEMPORAL/////////////// */
	virtual char* toString();

};

#endif
