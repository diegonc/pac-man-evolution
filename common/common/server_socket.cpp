#include "server_socket.h"

Socket_Server::Socket_Server():Socket(){}

Socket_Server::Socket_Server(int descriptor):Socket(descriptor){}		
			
Socket_Server::~Socket_Server(){
	if(this->esta_descriptor_abierto())
		this->cerrar();		
}
void Socket_Server::bind_socket(std::string &direccion, unsigned short int puerto){
	try{
		bind_socket(inet_addr(direccion.c_str()), puerto);
	}
	catch(std::runtime_error &e){
		throw e;
	}
}
void Socket_Server::bind_socket(unsigned long direccion, unsigned short int puerto){
	if(this->esta_descriptor_abierto()){
		
		struct sockaddr_in mi_socket;

		mi_socket.sin_family = Socket::IPv4;
		//pone la direccion		
		mi_socket.sin_addr.s_addr = direccion;
		//pone el puerto
		mi_socket.sin_port = htons(puerto);
		//completa con 0		
		bzero(&(mi_socket.sin_zero),8);		
		
		//se conecta y recibe el error
		int error = bind (this->get_descriptor(), (struct sockaddr *)&mi_socket, 
				sizeof(struct sockaddr));
		if( error == -1){
			std::string mensaje_error = "Error - "; 
			mensaje_error += strerror(errno);
			throw std::runtime_error(mensaje_error.c_str());;
		}
	}
	else
		throw std::runtime_error("Error - El socket no fue creado.");		
}

void Socket_Server::bind_socket(unsigned short int puerto){
	try{
		bind_socket(Socket_Server::ESCUCHAR_TODOS, puerto);
	}
	catch(std::runtime_error &e){
		throw e;
	}
		
		
}

void Socket_Server::escuchar(){
	if(this->esta_descriptor_abierto()){
		int error = listen(this->get_descriptor(), NUM_CONEXIONES);
		if(error==-1){
			std::string mensaje_error = "Error - "; 
			mensaje_error += strerror(errno);
			throw std::runtime_error(mensaje_error.c_str());
		}
	}
	else	
		throw std::runtime_error("Error - El socket no fue creado.");	
}		
Socket_Cliente* Socket_Server::aceptar(){
	
	struct sockaddr cliente;
	socklen_t longitud_cliente = sizeof(struct sockaddr);
	
	if(this->esta_descriptor_abierto()){
		int descriptor_nuevo = accept(this->get_descriptor(),(struct sockaddr *)&cliente,
								&longitud_cliente);		
		
		if(descriptor_nuevo != -1){
			Socket_Cliente * socket_nuevo = new Socket_Cliente(descriptor_nuevo);
			return (socket_nuevo);
		}
		else{
			std::string mensaje_error = "Error - "; 
			mensaje_error += strerror(errno);
			throw std::runtime_error(mensaje_error.c_str());
		}
		
	}
	else	
		throw std::runtime_error("Error - El socket no fue creado.");			
}
