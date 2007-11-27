//Header
#include "pas_vert.h"

/* CLASE PASILLO VERT: Clase que representa un pasillo vertical. Desciende de estructural. Se conecta por las puntas.
   La orientacion es NORTE por defecto. */

/* Constructor: */

PasilloVert::PasilloVert (int pos_x, int pos_y) : Estructural(pos_x, pos_y, PAS_VERT_ANCHO, PAS_VERT_ALTO, NORTE ){
	this->set_habitable(0,0, true);
	this->set_habitable(1,0, true);
	this->set_habitable(2,0, true);
	S_ptr<Punto> conec1 (new Punto(pos_x - 1, pos_y));
	S_ptr<Punto> conec2 (new Punto(pos_x + PAS_VERT_ALTO, pos_y));
	this->set_posible_conexion(0,0, conec1);
	this->set_posible_conexion(2,0, conec2);
}

/* ///////////////TEMPORAL/////////////// */
char* PasilloVert::toString(){
	return "PASILLO VERTICAL";
}
