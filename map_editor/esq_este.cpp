//Header
#include "esq_este.h"

/* CLASE ESQUINA ESTE: Clase que representa una esquina que conecta el ESTE con el SUR. Su orientacion es ESTE. Hereda de estructural. */

/* Constructor: */

EsqEste::EsqEste (int pos_x, int pos_y) : Estructural(pos_x, pos_y, ESQ_ANCHO, ESQ_ALTO, ESTE ){
	this->set_habitable(0,0, true);
	this->set_habitable(0,1, true);
	this->set_habitable(1,0, true);
	this->set_habitable(1,1, false);
	S_ptr<Punto> conec1 (new Punto(pos_x, pos_y + ESQ_ANCHO));
	S_ptr<Punto> conec2 (new Punto(pos_x + ESQ_ALTO, pos_y));
	this->set_posible_conexion(0,1, conec1);
	this->set_posible_conexion(1,0, conec2);
}

/* Get Tipo: */

TipoElem EsqEste::get_tipo(){
	return ESQ;
}

/* Get Ruta Imagen: */

char* EsqEste::get_ruta_imagen(){
		return RUTA_ESQ_ESTE;
}

/* ///////////////TEMPORAL/////////////// */
char* EsqEste::toString(){
	return "ESQ ESTE";
}
