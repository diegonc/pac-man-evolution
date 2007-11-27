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

	/* ///////////////TEMPORAL/////////////// */
	virtual char* toString();

};

#endif
