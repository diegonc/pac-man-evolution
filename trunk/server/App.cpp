#include "App.h"
#include <string>
#include "ModeloServidor.h"
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
	
	S_ptr<ModeloServidor> modelo(new ModeloServidor());
	S_ptr<MundoBajoNivel> mundo(new MundoBasicImp());
	modelo->set_mundo(mundo);
	modelo->start();
	pthread_join(modelo->get_hilo(), NULL);
	
	return 0;
}
