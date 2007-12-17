#ifndef CLASS_OBSERVADOR
#define CLASS_OBSERVADOR

/***************************************************************************
-	Define una interfaz comun para que objetos se puedan subscribir a los
	observables y asi ser notificados de algun cambio.
***************************************************************************/


#include "observable.h"

class Observable;

class Observador{
	public:
		virtual ~Observador(){}
	
		virtual void actualizar(Observable * observable, void * param) = 0;
	
};

#endif
