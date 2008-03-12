//Header
#include <editor/bif_norte.h>

/* CLASE BIF NORTE: Clase que representa una bifurcacion con orientacion NORTE. Hereda de Estructural. */

/* Constructor: */

BifNorte::BifNorte (int pos_x, int pos_y) : Estructural(pos_x, pos_y, BIF_HORIZ_ANCHO, BIF_HORIZ_ALTO, NORTE ){

	this->set_habitable(0,0,false);
	this->set_habitable(0,2,false);
	
	S_ptr<Punto> conec1 (new Punto(pos_x - 1, pos_y + 1));
	S_ptr<Punto> conec2 (new Punto(pos_x + 1, pos_y - 1));
	S_ptr<Punto> conec3 (new Punto(pos_x + 1, pos_y + this->get_ancho()));
	
	this->set_posible_conexion(0,1,conec1);
	this->set_posible_conexion(1,0, conec2);
	this->set_posible_conexion(1,2, conec3);
}

/* Get Ruta Imagen: */

char* BifNorte::get_ruta_imagen(){
		return RUTA_BIF_NORTE;
}

/* Get Tipo: */

TipoElem BifNorte::get_tipo(){
		return BIFUR;	
}
