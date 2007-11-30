#include "Comestible.h"

const char Comestible::power_up = 0;
const char Comestible::quesito 	= 1;
const char Comestible::frutita 	= 2;

Comestible::Comestible(int puntos, Posicion &pos){
	this->puntaje = puntos;	
	this->p = pos;
	std::cout << this->p<<"\n";
}
	
Comestible::~Comestible(){}
	
int Comestible::get_puntos(){
	return this->puntaje;
}
Direccion Comestible::get_orientacion(){
	return Direccion::Norte;
}
Posicion& Comestible::get_posicion(){
	return this->p;
}
