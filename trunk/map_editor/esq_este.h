//Header
#ifndef Esq_Este_h_
#define Esq_Este_h_

//Incluyo las librerias necesarias
#include "estructural.h"
#include "punto.h"

/* CLASE ESQUINA ESTE: Clase que representa una esquina que conecta el ESTE con el SUR. Su orientacion es ESTE. Hereda de estructural. */

class EsqEste : public Estructural {

	public:

	/* Constructor: Inicializa una esquina este con las posiciones pasadas por parametros. */
	EsqEste (int pos_x, int pos_y);

	/* ///////////////TEMPORAL/////////////// */
	virtual char* toString();

};

#endif
