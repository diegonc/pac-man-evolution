#include "Estructural.h"

Estructural::Estructural(){}
	
void Estructural::set_arriba(S_ptr<Estructural> e){
	this->arriba = e;
	S_ptr<Estructural> sptr_this(this);
	e->set_abajo(sptr_this);
}
void Estructural::set_abajo(S_ptr<Estructural> e){
	this->abajo = e;
	S_ptr<Estructural> sptr_this(this);
	e->set_arriba(sptr_this);
}
void Estructural::set_derecha(S_ptr<Estructural> e){
	this->derecha = e;
	S_ptr<Estructural> sptr_this(this);
	e->set_izquierda(sptr_this);
}
void Estructural::set_izquierda(S_ptr<Estructural> e){
	this->izquierda = e;
	S_ptr<Estructural> sptr_this(this);
	e->set_derecha(sptr_this);
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
