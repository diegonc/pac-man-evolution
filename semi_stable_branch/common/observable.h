#ifndef CLASS_OBSERVABLE
#define CLASS_OBSERVABLE

/*****************************************************************************
-	Esta clase define metodos para agregar y avisar a los observadores algun
	cambio. No es abstracte e implementa todos los metodos necesarios.
***************************************************************************/

#include "observador.h"
#include "mutex.h"
#include "bloqueo.h"
#include <list>

class Observador;

class Observable{
	private: 
		Mutex llave;
	
		std::list<Observador *> observadores;
		bool cambio;
	
	public:
		Observable();
	
		~Observable();
		
		void set_cambio();
	
		void agregar_observador(Observador * observador);
	
		void avisar_observadores(void * param);
	
		void quitar_observador(Observador * observador);
	
};

#endif
