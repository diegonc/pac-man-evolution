//Header
#ifndef Casa_Oeste_h_
#define Casa_Oeste_h_

//Incluyo las librerias necesarias
#include "casa_fantasmas.h"
#include "punto.h"

/* CLASE CASA OESTE: Clase que representa una casa de fantasmas con orientacion OESTE. Hereda de CasaFantasmas. */

class CasaOeste : public CasaFantasmas {

	public:

	/* Constructor: Inicializa una casa oeste con las posiciones pasadas por parametros. */
	CasaOeste (int pos_x, int pos_y);

	/* Get Ruta Imagen: Devuelve una cadena con la ruta donde se encuentra la imagen que representa al elemento */
	virtual char* get_ruta_imagen();

	/* ///////////////TEMPORAL/////////////// */
	virtual char* toString();

};

#endif
