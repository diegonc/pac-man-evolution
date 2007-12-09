#include "Servidor.h"

#include "PaqueteInit.h"
#include "PaqueteStart.h"
#include "EscritorCliente.h"

#define _DEFAULT_CANT_MIN	2
#define _DEFAULT_CANT_MAX	10

const int Servidor::SENIAL_CANCELAR = SIGUSR1;	

void Servidor::manejador_signal(int num_signal){
	switch(num_signal){
		case Servidor::SENIAL_CANCELAR: break;
			
		default: raise(num_signal);				
	}
}
void Servidor::set_propiedades_signal(const int id_signal){
	//Setteo propiedades para la accion a realizarse con una señal
		this->accion_signal.sa_handler = manejador_signal;
		sigemptyset(&this->accion_signal.sa_mask);
		this->accion_signal.sa_flags = 0;//~SA_RESTART;
		sigaction(id_signal,&this->accion_signal, NULL);
	
}
Servidor::Servidor(std::string &direccion, unsigned short int puerto, S_ptr<ModeloServidor> mod) : modelo( mod )
{
	try{
		//creo el socket del servidor
		this->socket = new Socket_Server();
		//lo bindeo
		this->socket->bind_socket(direccion, puerto);
		//setteo las propieaddes de la senial para cortar el accept
		set_propiedades_signal(Servidor::SENIAL_CANCELAR);
		//asigno por defecto las cantidades minimas y maximas de jugadores
		this->cant_max_clientes = _DEFAULT_CANT_MIN;
		this->cant_min_clientes = _DEFAULT_CANT_MAX;
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
		
		set_propiedades_signal(Servidor::SENIAL_CANCELAR);
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
		while( !parar ) {
			//para saber si ya mando el start
			bool ya_mando_start = false;
			//empeiza a escuchar clientes
			socket->escuchar();
			//acepta un cliente
			Socket_Cliente* client = socket->aceptar();
			//lo agrega a la pileta de clietnes
			Cliente * cliente_nuevo = pool.lanzar_cliente( client );
			//agrega si jugador al modelo
			this->modelo->agregar_jugador(cliente_nuevo->get_jugador());
			//le manda el paquete init
			bool es_pacman = cliente_nuevo->get_jugador()->get_personaje()->get_tipo() == Personaje::pacman;
			S_ptr<Paquete> paquete_init(new PaqueteInit(es_pacman,modelo->get_mundo().get_mapa_activo()));
			cliente_nuevo->get_escritor().encolar_paquete(paquete_init);
			//si llego a la cantidad minima de clientes, le mando a todos los ya
			//conectados el start
			S_ptr<Paquete> paquete_start(new PaqueteStart(40)); //TODO: <<---CAMBIARRRARRR
			if( pool.get_cantidad_clientes() == cant_min_clientes && !ya_mando_start ){
				sleep(5);
				pool.mandar_mensaje_todos(paquete_start);
				ya_mando_start = true;
				//TODO ARRANCAR CON EL FUCKIN' MODELO
			}
			else{
				if( pool.get_cantidad_clientes() > cant_min_clientes &&
					pool.get_cantidad_clientes() < cant_max_clientes)
						cliente_nuevo->get_escritor().encolar_paquete(paquete_start);
			}
			if(pool.get_cantidad_clientes() == cant_max_clientes)
				parar = true;
		}
    } catch( std::runtime_error e ) {
	    // Si es interrumpido.
    }
    pool.join_all();
}

void Servidor::set_cant_min_clientes(unsigned int cant){
	if(cant < cant_max_clientes)
		cant_min_clientes = cant;
}
void Servidor::set_cant_max_clientes(unsigned int cant){
	if(cant > cant_min_clientes)
		cant_max_clientes = cant;	
	
}
