#ifndef __ESCRITOR_CLIENTE_H__
#define __ESCRITOR_CLIENTE_H__

#include "../common/thread.h"
#include "../common/bloqueo.h"
#include "../common/evento.h"
#include "Cliente.h"
#include "Paquete.h"
#include <queue>


class EscritorCliente : public Thread{
	private:
		Cliente	* cliente;
		bool debe_terminar;
		Mutex llave;		
		Evento e;
		
	
		std::queue< S_ptr<Paquete> > buffer;
	
		EscritorCliente(EscritorCliente &e);
	public:
		
		EscritorCliente(Cliente * c);
	
		~EscritorCliente();
		
		void run();
		
		void terminar();
	
		void encolar_paquete(S_ptr<Paquete> paquete);
};


#endif /*__ESCRITOR_CLIENTE_H__*/
