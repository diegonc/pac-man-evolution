#include "Estructural.h"

Estructural::Estructural(){}
	
void Estructural::set_arriba(S_ptr<Estructural> casillero){
	this->arriba = casillero;
}
void Estructural::set_abajo(S_ptr<Estructural> casillero){
	this->abajo = casillero;
}
void Estructural::set_derecha(S_ptr<Estructural> casillero){
	this->derecha = casillero;
}
void Estructural::set_izquierda(S_ptr<Estructural> casillero){
	this->izquierda = casillero;
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