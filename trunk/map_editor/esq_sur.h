//Header
#ifndef Esq_Sur_h_
#define Esq_Sur_h_

//Incluyo las librerias necesarias
#include "estructural.h"
#include "punto.h"

/* CLASE ESQUINA SUR: Clase que representa una esquina que conecta el SUR con el OESTE. Su orientacion es SUR. Hereda de estructural. */

class EsqSur : public Estructural {

	public:

	/* Constructor: Inicializa una esquina sur con las posiciones pasadas por parametros. */
	EsqSur (int pos_x, int pos_y);
	
	/* Get Tipo: Devuelve el tipo del elemento */
	virtual TipoElem get_tipo();

	/* Get Ruta Imagen: Devuelve una cadena con la ruta donde se encuentra la imagen que representa al elemento */
	virtual char* get_ruta_imagen();

	/* ///////////////TEMPORAL/////////////// */
	virtual char* toString();

};

#endif
