//Header
#include "bif_oeste.h"

/* CLASE BIF OESTE: Clase que representa una bifurcacion con orientacion OESTE. Hereda de Estructural. */

/* Constructor: */

BifOeste::BifOeste (int pos_x, int pos_y) : Estructural(pos_x, pos_y, BIF_VERT_ANCHO, BIF_VERT_ALTO, OESTE ){

	this->set_habitable(0,0,false);
	this->set_habitable(2,0,false);
	
	S_ptr<Punto> conec1 (new Punto(pos_x + 1, pos_y - 1));
	S_ptr<Punto> conec2 (new Punto(pos_x - 1, pos_y + 1));
	S_ptr<Punto> conec3 (new Punto(pos_x + this->get_alto(), pos_y + 1));
	
	this->set_posible_conexion(1,0,conec1);
	this->set_posible_conexion(0,1, conec2);
	this->set_posible_conexion(2,1, conec3);
}

/* Get Ruta Imagen: */

char* BifOeste::get_ruta_imagen(){
		return RUTA_BIF_OESTE;
}

/* Get Tipo: */

TipoElem BifOeste::get_tipo(){
		return BIFUR;	
}
