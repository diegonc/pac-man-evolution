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

        void lanzar_cliente( Socket_Cliente* sock );

        void join_all();
	
};

#endif /* __CLIENTPOOL_H__ */
