#include "App.h"
#include <string>
#include "ModeloServidor.h"
#include <pthread.h>

//para realizar las conversiones
#include "../map_editor/mundo.h"
#include "../map_editor/traductor.h"

S_ptr<App> App::instancia;

App::App(int argc, char *argv[]){
	this->argc = argc;
	this->argv = argv;
}
App::App(App& a){}
	
App::~App(){}
	
S_ptr<App> App::get_instancia(int argc, char *argv[]){
	if( instancia.es_nulo())
		instancia = S_ptr<App>(new App(argc, argv));
	return instancia;
}
int App::ejecutar(){
	//crea el modelo	
	S_ptr<ModeloServidor> modelo(new ModeloServidor());
	////////TODO....ACA SE HACE LA CARGA; AGREGAR UN PARSER DE LINEA DE COMANDOS
	//creo el mundo de alto nivel y lo cargo del xml
	Mundo mundo_alto_nivel;
	if( mundo_alto_nivel.fromXml(argv[1])	){
		//lo traduzo a un mundo de bajo nivel y lo meto en un smart Pointer
		Traductor traductor;
		S_ptr<MundoBajoNivel> mundo_bajo_nivel(traductor.traducir(&mundo_alto_nivel));
		//lo meto en el modelo
		modelo->set_mundo(mundo_bajo_nivel);
		//inicia el hilo del modelo
		modelo->start();
		//se une al hilo
		modelo->join();
		//pthread_join(modelo->get_hilo(), NULL);
	}
	else
		//TODO PROVISORIO
		std::cerr << "Hubo un error con la carga del xml\n";
	return 0;
}
