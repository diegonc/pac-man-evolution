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
   //Aviso a los observadores que un cliente se conecto
   this->set_cambio();
	this->avisar_observadores(c);
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
   //Busco al cliente y si lo encuentro lo saco de la lista de clientes
   std::list<Cliente*>::iterator it = this->buscar_interno(id_cliente);
   if (it != clientes.end()) {	
      Cliente* cliente = (*it);      
      this->clientes.erase(it);	   
      //Aviso a los observadores que un cliente se desconecto
	   this->set_cambio();
	   this->avisar_observadores(cliente);
	   //Elimino al cliente recien removido
	   delete(cliente);
   }
}

Cliente* ClientPool::buscar_cliente(unsigned int id_cliente){
   Cliente* cliente = NULL;
   std::list<Cliente*>::iterator it = this->buscar_interno(id_cliente);
   if (it != clientes.end())
      cliente = (*it);
   return cliente;
}

void ClientPool::actualizar(Observable* obs, void* param){
	//Casteo el parametro como cliente y lo quito de la pool
	Cliente* cliente = (Cliente*) param;
   this->quitar_cliente(cliente->get_id());
}

std::list<Cliente*>::iterator ClientPool::buscar_interno(unsigned int id_cliente){
   bool encontrado = false;
   std::list<Cliente*>::iterator it = this->clientes.begin();  
   while( it != clientes.end() && (!encontrado) ){
		if( (*it)->get_id() == id_cliente )
			encontrado = true;
		else
			it++;
	}
   return it;
}


