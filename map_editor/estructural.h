//Header
#ifndef Estructural_h_
#define Estructural_h_

//Incluyo las librerias necesarias
#include "elemento.h"

/* CLASE ESTRUCTURAL: Esta clase abstracta representa un elemento estructural y desciende de elemento. */

class Estructural : public Elemento {

	protected:

	/* Constructor: Inicializa el elemento con los datos pasados por parametro. */
	Estructural(int pos_x, int pos_y, int ancho, int alto, Orientacion orientacion);

	public:

	/* Destructor: Libera los recursos consumidos por el elemento. */
	virtual ~Estructural(){}

	/* Es Estructural: Devuelve true porque el elemento es estructural. */
	virtual bool es_estructural();
	
};

#endif
