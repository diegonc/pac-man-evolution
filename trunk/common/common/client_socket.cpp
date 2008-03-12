#include <common/client_socket.h>

Socket_Cliente::Socket_Cliente():Socket(){	
}
	
Socket_Cliente::Socket_Cliente(int descriptor):Socket(descriptor){}

Socket_Cliente::~Socket_Cliente(){
	if(this->esta_descriptor_abierto())
		this->cerrar();		
}
void Socket_Cliente::conectar(unsigned short int puerto){
	if(this->esta_descriptor_abierto()){
		
		struct sockaddr_in servidor;
		
		servidor.sin_family = Socket::IPv4;
		//pone la direccion		
		servidor.sin_addr.s_addr = Socket::ESCUCHAR_TODOS;
		//pone el puerto
		servidor.sin_port = htons(puerto);
		//completa con 0		
		bzero(&(servidor.sin_zero),8);		

		//se conecta y recibe el error
		int error = connect (this->get_descriptor(), (struct sockaddr *)&servidor, 
				sizeof(struct sockaddr));
		if( error ){
			std::string mensaje_error = "Error - "; 
			mensaje_error += strerror(errno);
			throw std::runtime_error(mensaje_error.c_str());
		}
	}
	else
		throw std::runtime_error("Error - El socket no fue creado");
}

void Socket_Cliente::conectar(std::string &direccion, unsigned short int puerto){
	//si no pasa direccion se conect a todos	
	if(this->esta_descriptor_abierto()){
		
		struct sockaddr_in servidor;
		
		servidor.sin_family = Socket::IPv4;
		//pone la direccion		
		servidor.sin_addr.s_addr = inet_addr(direccion.c_str());
		//pone el puerto
		servidor.sin_port = htons(puerto);
		//completa con 0		
		bzero(&(servidor.sin_zero),8);		

		//se conecta y recibe el error
		int error = connect (this->get_descriptor(), (struct sockaddr *)&servidor, 
				sizeof(struct sockaddr));
		//si hubo error lanzo una excepcion
		if( error ){
			std::string mensaje_error = "Error - "; 
			mensaje_error += strerror(errno);
			throw std::runtime_error(mensaje_error.c_str());
		}
	}
	else
		throw std::runtime_error("Error - El socket no fue creado");
}
