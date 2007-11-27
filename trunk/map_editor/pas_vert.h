//Header
#ifndef Pas_Vert_h_
#define Pas_Vert_h_

//Incluyo las librerias necesarias
#include "estructural.h"
#include "punto.h"

/* CLASE PASILLO VERT: Clase que representa un pasillo vertical. Desciende de estructural. Se conecta por las puntas.
   La orientacion es NORTE por defecto. */

class PasilloVert : public Estructural {

	public:

	/* Constructor: Inicializa un pasillo vertical con las coords pasadas por parametro. */
	PasilloVert (int pos_x, int pos_y);

	/* ///////////////TEMPORAL/////////////// */
	virtual char* toString();

};

#endif
