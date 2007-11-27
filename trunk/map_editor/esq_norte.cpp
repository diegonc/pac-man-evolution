//Header
#include "esq_norte.h"

/* CLASE ESQUINA NORTE: Clase que representa una esquina que conecta el NORTE con el ESTE. Su orientacion es NORTE. Hereda de estructural. */

/* Constructor: */

EsqNorte::EsqNorte (int pos_x, int pos_y) : Estructural(pos_x, pos_y, ESQ_ANCHO, ESQ_ALTO, NORTE ){
	this->set_habitable(0,0, true);
	this->set_habitable(0,1, false);
	this->set_habitable(1,0, true);
	this->set_habitable(1,1, true);
	S_ptr<Punto> conec1 (new Punto(pos_x - 1, pos_y));
	S_ptr<Punto> conec2 (new Punto(pos_x + 1, pos_y + ESQ_ANCHO));
	this->set_posible_conexion(0,0, conec1);
	this->set_posible_conexion(1,1, conec2);
}

/* ///////////////TEMPORAL/////////////// */
char* EsqNorte::toString(){
	return "ESQ NORTE";
}
