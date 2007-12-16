#ifndef __CLIENTPOOL_H__
#define __CLIENTPOOL_H__

#include <list>
#include "../common/Cliente.h"
#include "../common/observable.h"
#include "../common/observador.h"

class ClientPool : public Observable, public Observador {

    std::list<Cliente*> clientes;
    unsigned int num_orden;

    public:
        ClientPool();

        ~ClientPool();

        Cliente * lanzar_cliente( Socket_Cliente* sock );

        void join_all();
	
	const std::list<Cliente*> get_clientes();
	
	void mandar_mensaje_todos(S_ptr<Paquete> mensaje);
	
	unsigned int get_cantidad_clientes();
	
	void quitar_cliente(unsigned int id_cliente);

	void actualizar(Observable* obs, void* param);

};

#endif /* __CLIENTPOOL_H__ */
