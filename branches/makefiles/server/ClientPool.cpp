#include "ClientPool.h"

#include "EscritorCliente.h"

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
	return c;
}

void ClientPool::join_all()
{
    std::list<Cliente*>::iterator it = clientes.begin();
    while( it != clientes.end() )
        (*it)->join();
}

const std::list<Cliente*>& ClientPool::get_clientes(){
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
