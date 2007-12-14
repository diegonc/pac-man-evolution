#include "App.h"
#include <string>
#include "ModeloServidor.h"
#include "Servidor.h"

//para realizar las conversiones
#include "traductor.h"
//#include "../map_editor/mundo.h"


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
	////////TODO....ACA SE HACE LA CARGA; AGREGAR UN PARSER DE LINEA DE COMANDOS
	//creo el mundo de alto nivel y lo cargo del xml
	try{
		Mundo mundo_alto_nivel;
		if( mundo_alto_nivel.fromXml(argv[1])	){
			//lo traduzo a un mundo de bajo nivel y lo meto en un smart Pointer
			Traductor traductor;
			S_ptr<MundoBajoNivel> mundo_bajo_nivel(traductor.traducir(&mundo_alto_nivel));
			//crea el modelo	
			//S_ptr<ModeloServidor> modelo(new ModeloServidor());
			//lo meto en el modelo
			ModeloServidor::get_instancia()->set_mundo(mundo_bajo_nivel);
			//modelo->set_mundo(mundo_bajo_nivel);
			//crea el servidor
			S_ptr<Servidor> servidor(new Servidor(7777) );//TODO USAR EL ARG
			//inicia el hilo del modelo
			//modelo->start();
			//inicia el hilo del servidor
			servidor->start();
			
			//se une a los hilos
			//modelo->join();
			servidor->join();
			
		}
		else
			//TODO PROVISORIO
			std::cerr << "Hubo un error con la carga del xml\n";
	}
	catch(std::runtime_error &e){
		std::cerr << e.what()<<"\n";	
	}
	return 0;
}
