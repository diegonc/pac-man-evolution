//Header
#include <editor/bif_sur.h>

/* CLASE BIF SUR: Clase que representa una bifurcacion con orientacion SUR. Hereda de Estructural. */

/* Constructor: */

BifSur::BifSur (int pos_x, int pos_y) : Estructural(pos_x, pos_y, BIF_HORIZ_ANCHO, BIF_HORIZ_ALTO, SUR ){

	this->set_habitable(1,0,false);
	this->set_habitable(1,2,false);
	
	S_ptr<Punto> conec1 (new Punto(pos_x + this->get_alto(), pos_y + 1));
	S_ptr<Punto> conec2 (new Punto(pos_x, pos_y - 1));
	S_ptr<Punto> conec3 (new Punto(pos_x, pos_y + this->get_ancho()));
	
	this->set_posible_conexion(1,1,conec1);
	this->set_posible_conexion(0,0, conec2);
	this->set_posible_conexion(0,2, conec3);
}

/* Get Ruta Imagen: */

char* BifSur::get_ruta_imagen(){
		return RUTA_BIF_SUR;
}

/* Get Tipo: */

TipoElem BifSur::get_tipo(){
		return BIFUR;	
}
