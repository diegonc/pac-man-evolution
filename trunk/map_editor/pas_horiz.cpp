//Header
#include "pas_horiz.h"

/* CLASE PASILLO HORIZ: Clase que representa un pasillo horizontal. Desciende de estructural. Se conecta por las puntas.
   La orientacion es ESTE por defecto. */

/* Constructor: */

PasilloHoriz::PasilloHoriz (int pos_x, int pos_y) : Estructural(pos_x, pos_y, PAS_HORIZ_ANCHO, PAS_HORIZ_ALTO, ESTE ){
	this->set_habitable(0,0, true);
	this->set_habitable(0,1, true);
	this->set_habitable(0,2, true);
	S_ptr<Punto> conec1 (new Punto(pos_x, pos_y - 1));
	S_ptr<Punto> conec2 (new Punto(pos_x, pos_y + PAS_HORIZ_ANCHO));
	this->set_posible_conexion(0,0, conec1);
	this->set_posible_conexion(0,2, conec2);
}

/* Get Ruta Imagen: */

char* PasilloHoriz::get_ruta_imagen(){
		return RUTA_PAS_HORIZ;
}

/* ///////////////TEMPORAL/////////////// */
char* PasilloHoriz::toString(){
	return "PASILLO HORIZONTAL";
}
