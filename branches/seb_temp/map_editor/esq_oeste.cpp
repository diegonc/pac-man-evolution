//Header
#include "esq_oeste.h"

/* CLASE ESQUINA OESTE: Clase que representa una esquina que conecta el OESTE con el NORTE. Su orientacion es OESTE. Hereda de estructural. */

/* Constructor: */

EsqOeste::EsqOeste (int pos_x, int pos_y) : Estructural(pos_x, pos_y, ESQ_ANCHO, ESQ_ALTO, OESTE ){
	this->set_habitable(0,0, false);
	this->set_habitable(0,1, true);
	this->set_habitable(1,0, true);
	this->set_habitable(1,1, true);
	S_ptr<Punto> conec1 (new Punto(pos_x - 1, pos_y + 1));
	S_ptr<Punto> conec2 (new Punto(pos_x + 1, pos_y - 1));
	this->set_posible_conexion(0,1, conec1);
	this->set_posible_conexion(1,0, conec2);
}

/* Get Tipo: */

TipoElem EsqOeste::get_tipo(){
	return ESQ;
}

/* Get Ruta Imagen: */

char* EsqOeste::get_ruta_imagen(){
		return RUTA_ESQ_OESTE;
}
