//Header
#include "componente.h"

/* CLASE COMPONENTE: Representa un pedazo de elemento estructural que puede ser habitable o punto de conexion
   del elemento. */

/* Constructor: */

Componente::Componente(){
	this->habitable = true;
	S_ptr<Punto> pto_nulo;
	this->posib_conexion = pto_nulo;
}

/* Set Habitable: */

void Componente::set_habitable (bool habitable){
	this->habitable = habitable;
}

/* Set Posible Conexion: */

void Componente::set_posible_conexion (S_ptr<Punto> pto_conexion){
	this->posib_conexion = pto_conexion;
}

/* Es Habitable: */

bool Componente::es_habitable(){
	return this->habitable;
}

/* Es Pto Conexion: */

bool Componente::es_pto_conexion(){
	if (!this->posib_conexion.es_nulo())
		return true;
	else
		return false;
}

/* Get Posible Conexion: */

S_ptr<Punto> Componente::get_posible_conexion(){
	return this->posib_conexion;
}
