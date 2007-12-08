#include "Servidor.h"

Servidor::Servidor(std::string &direccion, unsigned short int puerto, ModeloServidor& mod) : modelo( mod )
{
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
Servidor::Servidor(unsigned short int puerto, ModeloServidor& mod) : modelo(mod)
{
	try{
		this->socket = new Socket_Server();
		this->socket->bind_socket(puerto);
		
	}
	catch (std::runtime_error &e){
		delete this->socket;
		throw e;	
	}
}
Servidor::~Servidor()
{
	if( socket )
		delete socket;
}
void Servidor::run(){
    try {
	socket->escuchar();
	while( true ) {
		Socket_Cliente* client = socket->aceptar();
		pool.lanzar_cliente( client );
		// TODO: si no hay lugar, no escuchar mas.
        }
    } catch( std::runtime_error e ) {
	    // Si es interrumpido.
    }
    pool.join_all();
}
