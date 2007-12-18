#ifndef CLASS_EVENTO
#define CLASS_EVENTO

#include "mutex.h"

class Evento{
	private:
		class Condicion {
			private:
				pthread_cond_t  condicion;
			public:
				Condicion();
			
				~Condicion();
		
				void esperar(Mutex * llave);
		
				void mandar_senial();
		};
		
		Mutex *llave;
		Condicion *condicion;
		bool esperando;		

	public:
		Evento();
	
		~Evento();
	
		void lanzar_evento();
	
		void esperar_activacion();

		bool esta_esperando();
			
};

#endif
