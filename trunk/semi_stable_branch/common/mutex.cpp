#include "mutex.h"

Mutex::Mutex(Mutex &m){
	this->llave = m.llave;
}
Mutex& Mutex::operator=(Mutex& m){
	this->llave = m.llave;
	return *this;
}

Mutex::Mutex(){
	pthread_mutex_init(& this->llave, NULL);
}
	
void Mutex::lock(){
	pthread_mutex_lock(& this->llave);
}
		
void Mutex::unlock(){
	pthread_mutex_unlock(& this->llave);
}
	
Mutex::~Mutex(){
	pthread_mutex_destroy(& this->llave);
}
pthread_mutex_t * Mutex::get_mutex(){
	return &(this->llave);	
}
