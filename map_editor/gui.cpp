//HEADER

#include "gui.h"

/* CLASE GUI: Representa la interfaz grafica de usuario del editor.
   Corre sobre un hilo propio de ejecucion, en el cual espera eventos. */

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

/* Run: */
	
void GUI::run(){
	//Muestro todos los widgets contenidos en la ventana y arranco a escuchar eventos
	this->ventana->mostrar();
	gtk_main ();
}

