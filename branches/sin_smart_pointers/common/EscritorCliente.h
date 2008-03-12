#ifndef __ESCRITOR_CLIENTE_H__
#define __ESCRITOR_CLIENTE_H__

#include "../common/thread.h"
#include "../common/bloqueo.h"
#include "../common/evento.h"
#include "../common/observable.h"
#include "Cliente.h"
#include "Paquete.h"
#include <queue>


class EscritorCliente : public Thread, public Observable {

	private:

		Cliente	* cliente;
		bool debe_terminar;
		Mutex llave;		
		Evento e;
		
	
		std::queue< Paquete * > buffer;
	
		EscritorCliente(EscritorCliente &e);
	public:
		
		EscritorCliente(Cliente * c);
	
		~EscritorCliente();
		
		void run();
		
		void terminar();
	
		void encolar_paquete(Paquete * paquete);
};


#endif /*__ESCRITOR_CLIENTE_H__*/
