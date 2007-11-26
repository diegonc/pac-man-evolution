//Header
#include "estructural.h"

/* CLASE ESTRUCTURAL: Esta clase abstracta representa un elemento estructural y desciende de elemento. */

/* Constructor: */

Estructural::Estructural(int pos_x, int pos_y, int ancho, int alto, Orientacion orientacion) : Elemento(pos_x, pos_y, ancho, alto, orientacion) {}

/* Es Estructural: */

bool Estructural::es_estructural(){
	return true;
}
