#include "MessageDispatcher.h"

S_ptr<MessageDispatcher> MessageDispatcher::instancia;

MessageDispatcher::MessageDispatcher(){
	PoolClientes=NULL;
}

MessageDispatcher::MessageDispatcher(MessageDispatcher &j){}

S_ptr<MessageDispatcher> MessageDispatcher::get_instancia(){
	if( instancia.es_nulo())
		instancia = S_ptr<MessageDispatcher>(new MessageDispatcher());
	return instancia;
}

void MessageDispatcher::set_PoolClientes(ClientPool* pool){
	PoolClientes=pool;
}

void MessageDispatcher::dispatch_message(S_ptr<Paquete> paqueteMensaje){
	if (PoolClientes!=NULL){
		PoolClientes->mandar_mensaje_todos(paqueteMensaje);
	}
}
