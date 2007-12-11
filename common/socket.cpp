#include "socket.h"

int Socket::TCP = SOCK_STREAM;
int Socket::UDP = SOCK_STREAM;
int Socket::IPv4 = AF_INET;
int Socket::ESCUCHAR_TODOS = INADDR_ANY;

#define _CANT_INTENTOS  15


Socket::Socket(){

	//creo un descriptor, si hubo problemas, lanza una excepcion
	this->descriptor = socket (Socket::IPv4, Socket::TCP, 0);
	if(this->descriptor == -1){
		std::string mensaje_error = "Error - "; 
		//obtengo el mensaje de error y lo copio ya que no se pierde
		mensaje_error += strerror(errno);
		throw std::runtime_error(mensaje_error.c_str());
	}
	//para reusar la dir
	int si = 1;
	setsockopt( this->descriptor, SOL_SOCKET, SO_REUSEADDR, &si, sizeof(int) );
}
Socket::Socket(int descriptor){
		if(descriptor != -1)
			this->descriptor = descriptor;		
		else
			throw std::runtime_error("Error - Invalid descriptor\n");	
}

Socket::~Socket(){

}
void Socket::cerrar(){
	if(this->esta_descriptor_abierto()){
		close(this->descriptor);
		this->descriptor = -1;
	}
	
}

void Socket::escribir( const unsigned char* buf, int cant ) throw(std::runtime_error)
{
    int cant_recibidos =0;
	int retorno=0;
	int cantidad_intentos = 0;

	while( cant_recibidos < cant && cantidad_intentos < _CANT_INTENTOS ){
		//leo los datos	
		retorno = send(this->get_descriptor(), buf + cant_recibidos, cant - cant_recibidos, MSG_NOSIGNAL);
		//si devolvio -1 lanzo la excepcion
		if(retorno == -1 ){
			std::string mensaje_error = "Error - "; 
			mensaje_error += strerror(errno);
			throw std::runtime_error(mensaje_error.c_str());
		}
		cant_recibidos += retorno;
		cantidad_intentos++;
	}
}

void Socket::recibir( char* buf, int cant ) throw(std::runtime_error) {
	int cant_recibidos =0;
	int retorno=0;
	int cantidad_intentos = 0;

	while( cant_recibidos < cant && cantidad_intentos < _CANT_INTENTOS ){
		//leo los datos	
		retorno = recv(this->get_descriptor(), buf + cant_recibidos, cant - cant_recibidos, MSG_NOSIGNAL);
		//si devolvio -1 lanzo la excepcion
		if(retorno == -1 ){
			std::string mensaje_error = "Error - "; 
			mensaje_error += strerror(errno);
			throw std::runtime_error(mensaje_error.c_str());
		}
		cant_recibidos += retorno;
		cantidad_intentos++;
   }
}
/*
std::string Socket::recibir(int cant_caracteres){
	
	std::string mensaje_retorno;
	
	if(this->esta_descriptor_abierto()){
		//creo la cadena para el mensaje a recibir
		char * mensaje_recibido;
		mensaje_recibido = new char[cant_caracteres+1];
		//inicializo la ultima posicion en '\0' para cuando la copio
		mensaje_recibido[cant_caracteres] = '\0';
		int cant_recividos =0;
		int retorno=0;
		int cantidad_intentos = 0;
		
		while(cant_recividos < cant_caracteres && cantidad_intentos < 3){
			//leo los datos	
			retorno = recv(this->get_descriptor(), mensaje_recibido + cant_recividos, cant_caracteres - cant_recividos, MSG_NOSIGNAL);
			//si devolvio -1 lanzo la excepcion
			if(retorno == -1 ){
				std::string mensaje_error = "Error - "; 
				mensaje_error += strerror(errno);
				delete[] mensaje_recibido;
				throw std::runtime_error(mensaje_error.c_str());
			}
			cant_recividos += retorno;
			cantidad_intentos++;
		}
		//si todo salio bien, devuelvo el mensaje		
		mensaje_retorno = mensaje_recibido;
		delete[] mensaje_recibido;
	}
	return mensaje_retorno;
}*/
/*
void Socket::escribir(Socket * destino, std::string& cadena_a_enviar){
	
	if(this->esta_descriptor_abierto()){
		unsigned int cant_enviados=0;
		int cantidad_aux=0;
		int cantidad_intentos =0;
		
		while(cant_enviados < cadena_a_enviar.size() && cantidad_intentos < 3){
			//mando el mensaje
			cantidad_aux = send(destino->get_descriptor(), cadena_a_enviar.c_str()+ cant_enviados, cadena_a_enviar.size()-cant_enviados, MSG_NOSIGNAL);
			//si devolvio -1 quiere decir que el socket esta cerrado y lanzo la excepcion
			if(cantidad_aux == -1){
				std::string mensaje_error = "Error - "; 
				mensaje_error += strerror(errno);
				throw std::runtime_error(mensaje_error.c_str());
			}
			cant_enviados += cantidad_aux;
			cantidad_intentos++;
		}
		
	}
	else
		throw std::runtime_error("Error - No se puede enviar ya que no esta creado el socket");
}*/
int Socket::get_descriptor(){
	return this->descriptor;
}
bool Socket::esta_descriptor_abierto(){
	return descriptor >= 0;
}
