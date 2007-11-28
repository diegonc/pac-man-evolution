//Header
#include "esq_sur.h"

/* CLASE ESQUINA SUR: Clase que representa una esquina que conecta el SUR con el OESTE. Su orientacion es SUR. Hereda de estructural. */

/* Constructor: */

EsqSur::EsqSur (int pos_x, int pos_y) : Estructural(pos_x, pos_y, ESQ_ANCHO, ESQ_ALTO, SUR ){
	this->set_habitable(0,0, true);
	this->set_habitable(0,1, true);
	this->set_habitable(1,0, false);
	this->set_habitable(1,1, true);
	S_ptr<Punto> conec1 (new Punto(pos_x, pos_y-1));
	S_ptr<Punto> conec2 (new Punto(pos_x + ESQ_ALTO, pos_y + 1));
	this->set_posible_conexion(0,0, conec1);
	this->set_posible_conexion(1,1, conec2);
}

/* Get Ruta Imagen: */

char* EsqSur::get_ruta_imagen(){
		return RUTA_ESQ_SUR;
}

/* ///////////////TEMPORAL/////////////// */
char* EsqSur::toString(){
	return "ESQ SUR";
}
