//Header
#include "cruce.h"

/* CLASE CRUCE: Clase que representa una una doble bifurcacion o cruce. Hereda de Estructural. */

/* Constructor: */

Cruce::Cruce (int pos_x, int pos_y) : Estructural(pos_x, pos_y, CRUCE_ANCHO, CRUCE_ALTO, NULA ){

	this->set_habitable(0,0,false);
	this->set_habitable(0,2,false);
	this->set_habitable(2,0,false);
	this->set_habitable(2,2,false);
	
	S_ptr<Punto> conec1 (new Punto(pos_x - 1, pos_y + 1)); //Norte
	S_ptr<Punto> conec2 (new Punto(pos_x + 1, pos_y + this->get_ancho())); //Este
	S_ptr<Punto> conec3 (new Punto(pos_x + this->get_alto(), pos_y + 1)); //Sur
	S_ptr<Punto> conec4 (new Punto(pos_x + 1, pos_y - 1)); //Oeste
	
	this->set_posible_conexion(0,1,conec1);
	this->set_posible_conexion(1,2, conec2);
	this->set_posible_conexion(2,1, conec3);
	this->set_posible_conexion(1,0, conec4);
}

/* Get Ruta Imagen: */

char* Cruce::get_ruta_imagen(){
		return RUTA_CRUCE;
}

/* Get Tipo: */

TipoElem Cruce::get_tipo(){
		return CRUCE;
}
