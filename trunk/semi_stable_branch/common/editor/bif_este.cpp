//Header
#include "bif_este.h"

/* CLASE BIF ESTE: Clase que representa una bifurcacion con orientacion ESTE. Hereda de Estructural. */

/* Constructor: */

BifEste::BifEste (int pos_x, int pos_y) : Estructural(pos_x, pos_y, BIF_VERT_ANCHO, BIF_VERT_ALTO, ESTE ){

	this->set_habitable(0,1,false);
	this->set_habitable(2,1,false);
	
	S_ptr<Punto> conec1 (new Punto(pos_x + 1, pos_y + this->get_ancho()));
	S_ptr<Punto> conec2 (new Punto(pos_x - 1, pos_y));
	S_ptr<Punto> conec3 (new Punto(pos_x + this->get_alto(), pos_y));
	
	this->set_posible_conexion(1,1,conec1);
	this->set_posible_conexion(0,0, conec2);
	this->set_posible_conexion(2,0, conec3);
}

/* Get Ruta Imagen: */

char* BifEste::get_ruta_imagen(){
		return RUTA_BIF_ESTE;
}

/* Get Tipo: */

TipoElem BifEste::get_tipo(){
		return BIFUR;	
}
