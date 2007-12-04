#include "EstructuralUnitario.h"
#include <iostream>

EstructuralUnitario::Enum_Estructural EstructuralUnitario::Casa_Fanstasma 	= _CASA_FANTASMA;
EstructuralUnitario::Enum_Estructural EstructuralUnitario::Pasillo		  	= _PASILLO;
EstructuralUnitario::Enum_Estructural EstructuralUnitario::Salida_Pacman	= _SALIDA_PACMAN;


EstructuralUnitario::EstructuralUnitario(Posicion &p){
	this->set_posicion(p);
}

S_ptr<EstructuralUnitario> EstructuralUnitario::get_vecino(Direccion &direccion){
	if(direccion.get_dir() == Direccion::Norte)
		return this->get_arriba();
	else{
		if(direccion.get_dir() == Direccion::Sur)
			return this->get_abajo();
		else{
			if(direccion.get_dir() == Direccion::Este)
				return this->get_derecha();
			else
				return this->get_izquierda();
		}
	}
}

EstructuralUnitario::~EstructuralUnitario(){}

S_ptr<Comestible> EstructuralUnitario::get_comida(){
	S_ptr<Comestible> nulo;
	return nulo;
}
	
void EstructuralUnitario::set_arriba(S_ptr<EstructuralUnitario> e){
	this->arriba = e;
}
void EstructuralUnitario::set_abajo(S_ptr<EstructuralUnitario> e){
	this->abajo = e;
}
void EstructuralUnitario::set_derecha(S_ptr<EstructuralUnitario> e){
	this->derecha = e;
}
void EstructuralUnitario::set_izquierda(S_ptr<EstructuralUnitario> e){
	this->izquierda = e;
}
S_ptr<EstructuralUnitario> EstructuralUnitario::get_arriba(){
	return this->arriba;
}
S_ptr<EstructuralUnitario> EstructuralUnitario::get_abajo(){
	return this->abajo;
}
S_ptr<EstructuralUnitario> EstructuralUnitario::get_derecha(){
	return this->derecha;
}
			
S_ptr<EstructuralUnitario> EstructuralUnitario::get_izquierda(){
	return this->izquierda;
}

void EstructuralUnitario::set_posicion(Posicion &p){
	this->posicion = p;	
}
Posicion& EstructuralUnitario::get_posicion(){
	return this->posicion;
}
bool EstructuralUnitario::es_salida_pacman(){
	return false; //por defecto	
}
bool EstructuralUnitario::es_casa_fantasma(){
	return false;//por defecto
}
