#include "Comestible.h"

const char Comestible::power_up = 0;
const char Comestible::quesito 	= 1;
const char Comestible::frutita 	= 2;

Comestible::Comestible(int puntos){
	this->puntaje = puntos;	
}
	
Comestible::~Comestible(){}
	
int Comestible::get_puntos(){
	return this->puntaje;
}
