//HEADER

#include "gui.h"

/* CLASE GUI: Representa la interfaz grafica de usuario del editor.
   Corre sobre un hilo propio de ejecucion, en el cual espera eventos. */

GUI* GUI::instancia = NULL;

//Constructor:

GUI::GUI(int &argc, char** &argv){
	//Inicializo gtk
	gtk_init(&argc, &argv);
	
	//Creo la ventana principal
	this->ventana = new VPrincipal();
}

//Destructor:

GUI::~GUI(){
	delete(this->ventana);
}

/* Get Instance: */
GUI* GUI::get_instance(int argc, char* argv[]){
	if (instancia == NULL)
		instancia = new GUI(argc, argv);
	return instancia;
}

/* Run: */
	
void GUI::run(){
	//Muestro todos los widgets contenidos en la ventana y arranco a escuchar eventos
	this->ventana->mostrar();
	gtk_main ();
}

/* Destroy: */

void GUI::destroy(){
	delete(instancia);
}

/* Get Ventana Principal: */

VPrincipal* GUI::get_ventana_principal(){
	return this->ventana;
}
