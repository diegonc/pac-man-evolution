#include "thread.h"

void Thread::start(){
	this->set_corriendo(true);
	pthread_create(& (this->get_hilo()), NULL, & (Thread::funcion_auxiliar_run), this);
}

void Thread::join(){
	// if(esta_corriendo) - Pa evitar leaks
		pthread_join(this->get_hilo(), NULL);
}
int Thread::thread_kill(int signal){
	return pthread_kill(hilo, signal);	
}
pthread_t& Thread::get_hilo(){
	return this->hilo;
}
Thread::~Thread(){}	

Thread::Thread(){}	

Thread::Thread(Thread &t){}
	
Thread& Thread::operator=(Thread& t){
	return t;
}
	
void * Thread::funcion_auxiliar_run(void * param){
	((Thread*)param)->run();
	((Thread*)param)->set_corriendo(false);
	return NULL;
}

void Thread::set_corriendo(bool corriendo){
	esta_corriendo = corriendo;
}

bool Thread::corriendo(){
	return this->esta_corriendo;
}
