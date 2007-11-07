#include "bloqueo.h"
#include <iostream>

Bloqueo::Bloqueo(Mutex * m):mutex(m){
	this->mutex->lock();
}
Bloqueo::~Bloqueo(){
	this->mutex->unlock();
}
