#ifndef __CLIENTE_H__
#define __CLIENTE_H__

#include "../../common/client_socket.h"
#include "../../common/thread.h"
#include "../../common/smart_pointer.h"
#include "../../server/Paquete.h"
#include <string>

class Cliente : public Thread
{
    std::string ip;
    short port;
    Socket_Cliente socket;

    public:
        Cliente( const std::string& ip, short port );
	
	void enviar_mensaje(S_ptr<Paquete> paquete);
		
	S_ptr<Paquete> recibir_mensaje();

        void run();
};

#endif /* __CLIENTE_H__ */
