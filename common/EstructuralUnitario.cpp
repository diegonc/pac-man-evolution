#include "EstructuralUnitario.h"
#include <iostream>

//definiciones
EstructuralUnitario::Enum_Estructural EstructuralUnitario::Casa_Fantasma 	= _CASA_FANTASMA;
EstructuralUnitario::Enum_Estructural EstructuralUnitario::Pasillo		= _PASILLO;
EstructuralUnitario::Enum_Estructural EstructuralUnitario::Salida_Pacman	= _SALIDA_PACMAN;


EstructuralUnitario::EstructuralUnitario(Posicion &p){
	this->set_posicion(p);
}

S_ptr<EstructuralUnitario> EstructuralUnitario::get_vecino(Direccion &direccion){
	//vtraduce la dureccion con la posicion
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
//bool EstructuralUnitario::es_salida_pacman(){
	//return false; //por defecto	
//}
//bool EstructuralUnitario::es_casa_fantasma(){
	//return false;//por defecto
//}
bool EstructuralUnitario::tiene_conexion(S_ptr<EstructuralUnitario> e){
	if(e == get_arriba() )
		return true;		
	if(e == get_abajo() )
		return true;
	if(e == get_derecha() )
		return true;
	if(e == get_izquierda() )
		return true;
	if(&(*e) == this)
		return true;
	return false;
}
