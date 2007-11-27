#include "Estructural.h"
#include <iostream>

Estructural::Estructural(){}

S_ptr<Estructural> Estructural::get_vecino(Direccion &direccion){
	if(&direccion == &Direccion::Norte)
		return this->get_arriba();
	else{
		if(&direccion == &Direccion::Sur)
			return this->get_abajo();
		else{
			if(&direccion == &Direccion::Este)
				return this->get_izquierda();
			else
				return this->get_derecha();
		}
	}
}
Estructural::~Estructural(){}
void Estructural::set_arriba(S_ptr<Estructural> e){
	this->arriba = e;
}
void Estructural::set_abajo(S_ptr<Estructural> e){
	this->abajo = e;
}
void Estructural::set_derecha(S_ptr<Estructural> e){
	this->derecha = e;
}
void Estructural::set_izquierda(S_ptr<Estructural> e){
	this->izquierda = e;
}
S_ptr<Estructural> Estructural::get_arriba(){
	return this->arriba;
}
S_ptr<Estructural> Estructural::get_abajo(){
	return this->abajo;
}
S_ptr<Estructural> Estructural::get_derecha(){
	return this->derecha;
}
			
S_ptr<Estructural> Estructural::get_izquierda(){
	return this->izquierda;
}
