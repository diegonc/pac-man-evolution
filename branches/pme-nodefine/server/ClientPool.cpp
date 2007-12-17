#include "ClientPool.h"

#include "../common/EscritorCliente.h"

ClientPool::ClientPool() : num_orden(0)
{

}

ClientPool::~ClientPool()
{
    std::list<Cliente*>::iterator it = clientes.begin();
    while( it != clientes.end() )
        delete (*it++);
}

Cliente * ClientPool::lanzar_cliente( Socket_Cliente* sock )
{
	Cliente* c = new Cliente( ++num_orden, sock );
    	c->start();
	clientes.push_back(c);
	//Agrego al pool como observador del cliente
	c->get_escritor().agregar_observador(this);
	return c;
}

void ClientPool::join_all()
{
    std::list<Cliente*>::iterator it = clientes.begin();
    while( it != clientes.end() )
        (*it)->join();
}

const std::list<Cliente*> ClientPool::get_clientes(){
	return this->clientes;	
}

void ClientPool::mandar_mensaje_todos(S_ptr<Paquete> mensaje){
	Cliente * cliente;
	
	std::list<Cliente*>::iterator it = clientes.begin();
    while( it != clientes.end() ){
		cliente = *it;
		cliente->get_escritor().encolar_paquete(mensaje);
		++it;
	}
}

unsigned int ClientPool::get_cantidad_clientes(){
	return this->clientes.size();
}

void ClientPool::quitar_cliente(unsigned int id_cliente){
	std::list<Cliente*>::iterator it = clientes.begin();
   	bool elimino = false;
	Cliente* cliente = NULL;	
	while( it != clientes.end() && !elimino ){
		if( (*it)->get_id() == id_cliente ){
			cliente = *it;
			clientes.erase(it);
			elimino = true;
			//Aviso a los observadores que un cliente se desconecto
			this->set_cambio();
			this->avisar_observadores(cliente);
		}
		else
			it++;
	}
	std::cout << "Deleteo al cliente: " << cliente->get_id() << std::endl << std::flush;
	//Elimino al cliente recien removido
	delete(cliente);
}

void ClientPool::actualizar(Observable* obs, void* param){
	//Casteo el parametro como cliente y lo quito de la pool
	Cliente* cliente = (Cliente*) param;
	std::cout << "Se desconecta el cliente: " << cliente->get_id() << std::endl << std::flush;
	this->quitar_cliente(cliente->get_id());
}

