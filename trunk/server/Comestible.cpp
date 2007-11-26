#include "Comestible.h"

Comestible::Comestible(int puntos){
	this->puntaje = puntos;	
}
	
Comestible::~Comestible(){}
	
int Comestible::get_puntos(){
	return this->puntaje;
}
