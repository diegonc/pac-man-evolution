#include "bloqueo.h"

Bloqueo::Bloqueo(Mutex * m):mutex(m){
	this->mutex->lock();
}
Bloqueo::~Bloqueo(){
	this->mutex->unlock();
}
