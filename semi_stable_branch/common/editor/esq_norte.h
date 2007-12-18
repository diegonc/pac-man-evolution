//Header
#ifndef Esq_Norte_h_
#define Esq_Norte_h_

//Incluyo las librerias necesarias
#include "estructural.h"
#include "punto.h"

/* CLASE ESQUINA NORTE: Clase que representa una esquina que conecta el NORTE con el ESTE. Su orientacion es NORTE. Hereda de estructural. */

class EsqNorte : public Estructural {

	public:

	/* Constructor: Inicializa una esquina norte con las posiciones pasadas por parametros. */
	EsqNorte (int pos_x, int pos_y);
	
	/* Get Tipo: Devuelve el tipo del elemento */
	virtual TipoElem get_tipo();
	
	/* Get Ruta Imagen: Devuelve una cadena con la ruta donde se encuentra la imagen que representa al elemento */
	virtual char* get_ruta_imagen();

};

#endif
