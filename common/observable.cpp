#include "observable.h"

Observable::Observable(){}
	
Observable::~Observable(){
	this->observadores.clear();
}
void Observable::set_cambio(){
	Bloqueo b(&this->llave);
	
	this->cambio = true;	
}
void Observable::avisar_observadores(void *param){
	//bloqueo para hacerlo thread safety
	Bloqueo b(&this->llave);
	
	if(this->cambio == true){
		std::list<Observador *>::iterator it = this->observadores.begin();
		//recorro todos los observadores y les aviso
		while( it != this->observadores.end() ){
			Observador * obs = *it;
         obs->actualizar(this,param);
			++it;
		}
		this->cambio = false;
	}
	
}
void Observable::quitar_observador(Observador * observador){
	//bloqueo para hacerlo thread safety
	Bloqueo b(&this->llave);
	this->observadores.remove(observador);
}
void Observable::agregar_observador(Observador * observador){
	//bloqueo para hacerlo thread safety
	Bloqueo b(&this->llave);
	if(observador != NULL)
		this->observadores.push_back(observador);
}
