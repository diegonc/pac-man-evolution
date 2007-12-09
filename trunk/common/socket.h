#ifndef CLASS_SOCKET
#define CLASS_SOCKET

/****************************************************************************
-	Esta clase define un socket en general. No se puede instanciar ya que no
	tiene sentido.
-	Implementa los metodos enviar y recivir comun a todos los sockets.

******************************************************************************/
#include <sys/socket.h>
#include <sys/types.h>
#include <stdexcept>
#include <arpa/inet.h>
#include <netdb.h>
#include <string>
#include <iostream>
#include <errno.h>
#include "bloqueo.h"

class Socket{
	private:
		Mutex llave_lectura;
		Mutex llave_escritura;
	
	protected:
		Socket();
			
		Socket(int descriptor);
	
	public:
		
		int descriptor;
		//definiciones para poder ser usadas, sin tener que conocer las de 
		//<sys/sockets.h>
		static int TCP;
		static int UDP;
		static int IPv4;
		static int ESCUCHAR_TODOS;
	
		virtual ~Socket();

		void cerrar();

		//std::string recibir(int cant_caracteres) throw(std::runtime_error);

		/* estas dos son para que no se corten los datos en los \0. */
		void recibir( char* buf, int cant ) throw(std::runtime_error);
	
		void escribir( const unsigned char* buf, int cant ) throw(std::runtime_error);

		//void escribir(Socket * destino, std::string& cadena_a_enviar) throw(std::runtime_error);
		
		int get_descriptor();
	
		bool esta_descriptor_abierto();
		

};


#endif
