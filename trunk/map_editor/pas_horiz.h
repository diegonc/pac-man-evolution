//Header
#ifndef Pas_Horiz_h_
#define Pas_Horiz_h_

//Incluyo las librerias necesarias
#include "estructural.h"
#include "punto.h"

/* CLASE PASILLO HORIZ: Clase que representa un pasillo horizontal. Desciende de estructural. Se conecta por las puntas.
   La orientacion es ESTE por defecto. */

class PasilloHoriz : public Estructural {

	public:

	/* Constructor: Inicializa un pasillo horizontal con las coords pasadas por parametro. */
	PasilloHoriz (int pos_x, int pos_y);

	/* ///////////////TEMPORAL/////////////// */
	virtual char* toString();

};

#endif
