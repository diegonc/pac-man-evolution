#include "thread.h"

void Thread::start(){
	pthread_create(& (this->get_hilo()), NULL, & (Thread::funcion_auxiliar_run), this);
}
/*void Thread::join(Thread *t){
	pthread_join(t->get_hilo(), NULL);
}
void Thread::join(pthread_t hilo){
	pthread_join(this->get_hilo(), NULL);
}*/
void Thread::join(){
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
	return NULL;
}
