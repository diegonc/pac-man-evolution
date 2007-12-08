#include "Servidor.h"

const int Servidor::SENIAL_CANCELAR = SIGUSR1;	

void Servidor::manejador_signal(int num_signal){
	switch(num_signal){
		case Servidor::SENIAL_CANCELAR: break;
			
		default: raise(num_signal);				
	}
}

Servidor::Servidor(std::string &direccion, unsigned short int puerto, S_ptr<ModeloServidor> mod) : modelo( mod )
{
	try{
		//creo el socket del servidor
		this->socket = new Socket_Server();
		//lo bindeo
		this->socket->bind_socket(direccion, puerto);
		//Setteo propiedades para la accion a realizarse con una señal
		this->accion_signal.sa_handler = manejador_signal;
		sigemptyset(&this->accion_signal.sa_mask);
		this->accion_signal.sa_flags = 0;//~SA_RESTART;
		sigaction(Thread_Aceptar_Clientes::SENIAL_CANCELAR,&this->accion_signal, NULL);
		
	}
	catch (std::runtime_error &e){
		//si hubo error borro el socket que seguro se creo
		delete this->socket; 
		throw e;	
	}
}
Servidor::Servidor(unsigned short int puerto, S_ptr<ModeloServidor> mod) : modelo(mod)
{
	try{
		this->socket = new Socket_Server();
		this->socket->bind_socket(puerto);
		//Setteo propiedades para la accion a realizarse con una señal
		this->accion_signal.sa_handler = manejador_signal;
		sigemptyset(&this->accion_signal.sa_mask);
		this->accion_signal.sa_flags = 0;//~SA_RESTART;
		sigaction(Thread_Aceptar_Clientes::SENIAL_CANCELAR,&this->accion_signal, NULL);
		
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
 	parar = false;  
	try {
		socket->escuchar();
		while( !parar ) {
			Socket_Cliente* client = socket->aceptar();
			pool.lanzar_cliente( client );
			// TODO: si no hay lugar, no escuchar mas.
        }
    } catch( std::runtime_error e ) {
	    // Si es interrumpido.
    }
    pool.join_all();
}
