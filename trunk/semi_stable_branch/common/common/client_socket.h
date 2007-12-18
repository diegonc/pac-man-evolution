#ifndef CLASS_SOCKET_CLIENTE
#define CLASS_SOCKET_CLIENTE

/*****************************************************************************
-	Esta clase implementa el socket para un cliente, es decir, tiene
	la posibilidad de conectarse a un servidor

*****************************************************************************/

#include <common/socket.h>
class Socket_Cliente : public Socket{
	
	public:
		
		Socket_Cliente();
			
		Socket_Cliente(int descriptor);
		
		~Socket_Cliente();
	
		void conectar(std::string &direccion, unsigned short int puerto);
	
		void conectar(unsigned short int puerto);
};

#endif
