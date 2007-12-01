//Header
#ifndef Esq_Oeste_h_
#define Esq_Oeste_h_

//Incluyo las librerias necesarias
#include "estructural.h"
#include "punto.h"

/* CLASE ESQUINA OESTE: Clase que representa una esquina que conecta el OESTE con el NORTE. Su orientacion es OESTE. Hereda de estructural. */

class EsqOeste : public Estructural {

	public:

	/* Constructor: Inicializa una esquina oeste con las posiciones pasadas por parametros. */
	EsqOeste (int pos_x, int pos_y);
	
	/* Get Tipo: Devuelve el tipo del elemento */
	virtual TipoElem get_tipo();

	/* Get Ruta Imagen: Devuelve una cadena con la ruta donde se encuentra la imagen que representa al elemento */
	virtual char* get_ruta_imagen();

	/* ///////////////TEMPORAL/////////////// */
	virtual char* toString();

};

#endif
