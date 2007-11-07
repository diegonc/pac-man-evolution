#include "evento.h"

Evento::Evento(){
	this->llave = new Mutex();
	this->condicion = new Condicion();
}
Evento::~Evento(){
	delete this->llave;	
	delete this->condicion;
}
void Evento::lanzar_evento(){
	this->condicion->mandar_senial();
}
	
void Evento::esperar_activacion(){
	this->condicion->esperar(this->llave);
}
Evento::Condicion::Condicion(){
	pthread_cond_init(&this->condicion, NULL); 
}
Evento::Condicion::~Condicion(){
	pthread_cond_destroy(&this->condicion);	
}
void Evento::Condicion::esperar(Mutex * llave){
	llave->lock();
	pthread_cond_wait(&this->condicion, llave->get_mutex());		
	llave->unlock();
}
void Evento::Condicion::mandar_senial(){
	pthread_cond_signal(&this->condicion);
}
