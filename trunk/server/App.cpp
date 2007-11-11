#include "App.h"

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
	return 0;
}
