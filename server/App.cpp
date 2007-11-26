#include "App.h"
#include <string>
#include "Modelo.h"
#include <pthread.h>

S_ptr<App> App::instancia;

App::App(){}
App::App(App& a){}
	
App::~App(){}
	
S_ptr<App> App::get_instancia(){
	if( instancia.es_nulo())
		instancia = S_ptr<App>(new App());
	return instancia;
}
int App::ejecutar(){
	std::string ruta = "a";
	S_ptr<Modelo> modelo(new Modelo(ruta));
	modelo->start();
	pthread_join(modelo->get_hilo(), NULL);
	
	return 0;
}
