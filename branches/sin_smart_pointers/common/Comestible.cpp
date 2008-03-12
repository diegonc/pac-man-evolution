#include "Comestible.h"

Comestible::Enum_Comestible Comestible::power_up    = _POWER_UP;
Comestible::Enum_Comestible Comestible::quesito 	= _QUESITO;
Comestible::Enum_Comestible Comestible::frutita 	= _FRUTITA;

Comestible::Comestible(int puntos, Posicion &pos){
	this->puntaje = puntos;	
	this->p = pos;
	this->invalido = false;
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
void Comestible::set_invalido(){
	this->invalido = true;
}
bool Comestible::es_invalido(){
	return this->invalido;
}
