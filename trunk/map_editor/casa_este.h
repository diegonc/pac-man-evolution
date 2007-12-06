//Header
#ifndef Casa_Este_h_
#define Casa_Este_h_

//Incluyo las librerias necesarias
#include "casa_fantasmas.h"
#include "punto.h"

/* CLASE CASA ESTE: Clase que representa una casa de fantasmas con orientacion ESTE. Hereda de CasaFantasmas. */

class CasaEste : public CasaFantasmas {

	public:

	/* Constructor: Inicializa una casa este con las posiciones pasadas por parametros. */
	CasaEste (int pos_x, int pos_y);

	/* Get Ruta Imagen: Devuelve una cadena con la ruta donde se encuentra la imagen que representa al elemento */
	virtual char* get_ruta_imagen();

	/* ///////////////TEMPORAL/////////////// */
	virtual char* toString();

};

#endif
