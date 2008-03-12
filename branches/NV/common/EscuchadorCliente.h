#ifndef __ESCUCHADOR_CLIENTE_H__
#define __ESCUCHADOR_CLIENTE_H__

#include "../common/thread.h"
#include "Cliente.h"

class EscuchadorCliente : public Thread{
	private:
		Cliente * cliente;
	
		EscuchadorCliente(EscuchadorCliente &e);
	public:
		
		EscuchadorCliente(Cliente * c);
	
		~EscuchadorCliente();
		
		void run();
		
};


#endif /*__ESCUCHADOR_CLIENTE_H__*/
