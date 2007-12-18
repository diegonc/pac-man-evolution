#ifndef MESSAGEDISPATCHER_H
#define MESSAGEDISPATCHER_H

#include <common/smart_pointer.h>
#include "ClientPool.h"

class MessageDispatcher{
	
	static S_ptr<MessageDispatcher> instancia;

	MessageDispatcher();

	MessageDispatcher(MessageDispatcher &j);

	ClientPool* PoolClientes;

	public:

	
		
	static S_ptr<MessageDispatcher> get_instancia();

	void set_PoolClientes(ClientPool* pool);

	void dispatch_message(S_ptr<Paquete> paqueteMensaje);

};


#endif
