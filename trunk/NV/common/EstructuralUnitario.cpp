#include "EstructuralUnitario.h"
#include <iostream>

//definiciones
EstructuralUnitario::Enum_Estructural EstructuralUnitario::Casa_Fantasma 	= _CASA_FANTASMA;
EstructuralUnitario::Enum_Estructural EstructuralUnitario::Pasillo		= _PASILLO;
EstructuralUnitario::Enum_Estructural EstructuralUnitario::Salida_Pacman	= _SALIDA_PACMAN;


EstructuralUnitario::EstructuralUnitario(Posicion &p){
	this->set_posicion(p);
	this->arriba = 		NULL;
	this->abajo = 		NULL;
	this->derecha = 	NULL;
	this->izquierda = 	NULL;
}

EstructuralUnitario * EstructuralUnitario::get_vecino(Direccion &direccion){
	//EstructuralUnitario * e = NULL;
	
	//traduce la dureccion con la posicion
	switch(direccion.get_dir()){
		case _NORTE:
			return this->get_arriba();
		case _SUR:
			return this->get_abajo();
		case _ESTE:
			return this->get_derecha();
		case _OESTE:
			return this->get_izquierda();
	}
}

EstructuralUnitario::~EstructuralUnitario(){
		
}

Comestible *  EstructuralUnitario::get_comida(){
	return NULL;
}
	
void EstructuralUnitario::set_arriba(EstructuralUnitario * e){
	this->arriba = e;
}
void EstructuralUnitario::set_abajo(EstructuralUnitario * e){
	this->abajo = e;
}
void EstructuralUnitario::set_derecha(EstructuralUnitario * e){
	this->derecha = e;
}
void EstructuralUnitario::set_izquierda(EstructuralUnitario * e){
	this->izquierda = e;
}
EstructuralUnitario * EstructuralUnitario::get_arriba(){
	return this->arriba;
}
EstructuralUnitario * EstructuralUnitario::get_abajo(){
	return this->abajo;
}
EstructuralUnitario * EstructuralUnitario::get_derecha(){
	return this->derecha;
}
			
EstructuralUnitario * EstructuralUnitario::get_izquierda(){
	return this->izquierda;
}
void EstructuralUnitario::set_posicion(Posicion &p){
	this->posicion = p;	
}
Posicion& EstructuralUnitario::get_posicion(){
	return this->posicion;
}
bool EstructuralUnitario::tiene_conexion(EstructuralUnitario * e){
	if(e == NULL)
		return false;
	
	if(e == get_arriba() )
		return true;		
	if(e == get_abajo() )
		return true;
	if(e == get_derecha() )
		return true;
	if(e == get_izquierda() )
		return true;
	if(e == this)
		return true;
	return false;
}
void EstructuralUnitario::set_comida(Comestible * comestible){}
