//Header
#ifndef Casa_Norte_h_
#define Casa_Norte_h_

//Incluyo las librerias necesarias
#include "casa_fantasmas.h"
#include "punto.h"

/* CLASE CASA NORTE: Clase que representa una casa de fantasmas con orientacion NORTE. Hereda de CasaFantasmas. */

class CasaNorte : public CasaFantasmas {

	public:

	/* Constructor: Inicializa una casa norte con las posiciones pasadas por parametros. */
	CasaNorte (int pos_x, int pos_y);

	/* Get Ruta Imagen: Devuelve una cadena con la ruta donde se encuentra la imagen que representa al elemento */
	virtual char* get_ruta_imagen();

};

#endif
