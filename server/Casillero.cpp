#include "Casillero.h"

Casillero::Casillero(){}
	
void Casillero::set_arriba(S_ptr<Casillero> casillero){
	this->arriba = casillero;
}
void Casillero::set_abajo(S_ptr<Casillero> casillero){
	this->abajo = casillero;
}
void Casillero::set_derecha(S_ptr<Casillero> casillero){
	this->derecha = casillero;
}
void Casillero::set_izquierda(S_ptr<Casillero> casillero){
	this->izquierda = casillero;
}
S_ptr<Casillero> Casillero::get_arriba(){
	return this->arriba;
}
S_ptr<Casillero> Casillero::get_abajo(){
	return this->abajo;
}
S_ptr<Casillero> Casillero::get_derecha(){
	return this->derecha;
}
			
S_ptr<Casillero> Casillero::get_izquierda(){
	return this->izquierda;
}
