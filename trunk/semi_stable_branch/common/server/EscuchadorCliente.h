#ifndef __ESCUCHADOR_CLIENTE_H__
#define __ESCUCHADOR_CLIENTE_H__

#include <common/thread.h>
#include <server/Cliente.h>
#include <errno.h>
#include <signal.h>

class EscuchadorCliente : public Thread{
	struct sigaction accion_signal;
	private:
		static void manejador_signal(int num_signal);

		void set_propiedades_signal(const int id_signal);		

		Cliente * cliente;
	
		EscuchadorCliente(EscuchadorCliente &e);
	public:
		static const int SENIAL_CANCELAR;		

		EscuchadorCliente(Cliente * c);
	
		~EscuchadorCliente();
		
		void run();
		
};


#endif /*__ESCUCHADOR_CLIENTE_H__*/
