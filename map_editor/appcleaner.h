//Header
#ifndef AppCleaner_h_
#define AppCleaner_h_

//Incluyo las librerias necesarias
#include "app.h"

/* CLASE APP CLEANER: Clase que se encarga de liberar los recursos de
   la aplicacion. */

class AppCleaner {
	public:
		//Constructor:
		AppCleaner(){}
		//Destructor: Libera los recursos de app.
		~AppCleaner();
	
};

#endif
