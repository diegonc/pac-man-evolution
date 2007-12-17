#ifndef CLASS_SOCKET_SERVER
#define CLASS_SOCKET_SERVER

/*****************************************************************************
-	Esta clase implementa un socket para un servidor, es decir, permite 
	escuchar y bind

*****************************************************************************/

#include "client_socket.h"
#include "socket.h"

#define NUM_CONEXIONES 5


class Socket_Server : public Socket{
	private:
		void bind_socket(unsigned long direccion, unsigned short int puerto);		
	
	public:
		Socket_Server();
			
		Socket_Server(int descriptor);	
	
		~Socket_Server();
		
		void bind_socket(std::string &direccion, unsigned short int puerto);
	
		void bind_socket(unsigned short int puerto);
	
		void escuchar();
	
		Socket_Cliente* aceptar();
		
};

#endif
