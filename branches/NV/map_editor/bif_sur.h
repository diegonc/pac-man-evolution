//Header
#ifndef Bif_Sur_h_
#define Bif_Sur_h_

//Incluyo las librerias necesarias
#include "estructural.h"
#include "punto.h"

/* CLASE BIF SUR: Clase que representa una bifurcacion con orientacion SUR. Hereda de Estructural. */

class BifSur : public Estructural {

	public:

	/* Constructor: Inicializa una bifurcacion con las posiciones pasadas por parametros. */
	BifSur (int pos_x, int pos_y);

	/* Get Ruta Imagen: Devuelve una cadena con la ruta donde se encuentra la imagen que representa al elemento */
	virtual char* get_ruta_imagen();
		
	/* Get Tipo: Devuelve el tipo del elemento */
	virtual TipoElem get_tipo();


};

#endif
