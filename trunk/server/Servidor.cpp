#include "Servidor.h"

Servidor::Servidor(std::string &direccion, unsigned short int puerto){
	try{
		//creo el socket del servidor
		this->socket = new Socket_Server();
		//lo bindeo
		this->socket->bind_socket(direccion, puerto);
	}
	catch (std::runtime_error &e){
		//si hubo error borro el socket que seguro se creo
		delete this->socket; 
		throw e;	
	}
}
Servidor::Servidor(unsigned short int puerto){
	try{
		this->socket = new Socket_Server();
		this->socket->bind_socket(puerto);
		
	}
	catch (std::runtime_error &e){
		delete this->socket;
		throw e;	
	}
}
Servidor::~Servidor(){

}
void Servidor::run(){
    try {
	while( true ) {
		Socket_Cliente* client = socket->aceptar();
		pool.lanzar_cliente( client );
        }
    } catch( std::runtime_error e ) {
	    // Si es interrumpido.
    }
    pool.join_all();
}
