#ifndef __CLIENTPOOL_H__
#define __CLIENTPOOL_H__

#include <list>
#include "Cliente.h"

class ClientPool
{
    std::list<Cliente*> clientes;
    unsigned int num_orden;

    public:
        ClientPool();

        ~ClientPool();

        Cliente * lanzar_cliente( Socket_Cliente* sock );

        void join_all();
	
		void mandar_mensaje( unsigned int id, S_ptr<Paquete> mensaje );
	
		void mandar_mensaje_todos(S_ptr<Paquete> mensaje);
	
		unsigned int get_cantidad_clientes();
};

#endif /* __CLIENTPOOL_H__ */