//Header
#include "app_editor.h"

/* CLASE APP EDITOR: Esta clase representa a la aplicacion en si. Tiene
   una sola instancia y un punto de acceso global a ella. */

AppEditor* AppEditor::instancia = NULL; //Inicializo la instancia en null
		
/* Constructor Privado: */
AppEditor::AppEditor(int argc, char* argv[]){
	this->gui = GUI::get_instance(argc, argv);
}

/* Destructor Privado: */
AppEditor::~AppEditor(){
}

/* Get Instance: */
AppEditor* AppEditor::get_instance(int argc, char* argv[]){
	//Si no existe la instancia creo una nueva y la seteo como instancia unica
	if (AppEditor::instancia == NULL)
		AppEditor::instancia = new AppEditor(argc, argv);
	return AppEditor::instancia;	//Devuelvo la instancia
}		

/* Ejecutar: */
void AppEditor::ejecutar(){
  //Hago arrancar la interfaz grafica
  gui->start();
  //Uno la interfaz grafica con el hilo principal, cuando termina
  gui->join(gui);
  GUI::destroy();
}


/* Destroy: */
void AppEditor::destroy(){
	delete(instancia);
}
