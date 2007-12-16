#include "Servidor.h"

#include "PaqueteInit.h"
#include "PaqueteStart.h"
#include "../common/EscritorCliente.h"
#include "AvisadorNovedades.h"

#define _DEFAULT_CANT_MIN	2
#define _DEFAULT_CANT_MAX	10

const int Servidor::SENIAL_CANCELAR = SIGUSR1;	

#include <unistd.h>


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
      this->accion_signal.sa_flags = SA_RESETHAND;
//		sigaction(id_signal,&this->accion_signal, NULL);
		sigaction(SIGSEGV,&this->accion_signal, NULL);
	
}
Servidor::Servidor(std::string &direccion, unsigned short int puerto)
{
	try{
		//creo el socket del servidor
		this->socket = new Socket_Server();
		//lo bindeo
		this->socket->bind_socket(direccion, puerto);
		//setteo las propieaddes de la senial para cortar el accept
		set_propiedades_signal(Servidor::SENIAL_CANCELAR);
		//asigno por defecto las cantidades minimas y maximas de jugadores
		this->cant_max_clientes = _DEFAULT_CANT_MAX;
		this->cant_min_clientes = _DEFAULT_CANT_MIN;
	}
	catch (std::runtime_error &e){
		//si hubo error borro el socket que seguro se creo
		delete this->socket; 
		throw e;	
	}
}
Servidor::Servidor(unsigned short int puerto)
{
	try{
		this->socket = new Socket_Server();
		this->socket->bind_socket(puerto);
		set_propiedades_signal(Servidor::SENIAL_CANCELAR);
		
		this->cant_max_clientes = _DEFAULT_CANT_MAX;
		this->cant_min_clientes = _DEFAULT_CANT_MIN;
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
 	
	AvisadorNovedades avisador(&this->pool);
	
	parar = false;  
	bool ya_mando_start = false;
	
	try {
		ModeloServidor::get_instancia()->get_mundo().get_mapa_activo()->agregar_observador(&avisador);
		//para saber si ya mando el start
		while( !parar ) {
			//empeiza a escuchar clientes
			socket->escuchar();
			//acepta un cliente
			Socket_Cliente* client = socket->aceptar();
			//lo agrega a la pileta de clietnes
			Cliente * cliente_nuevo = pool.lanzar_cliente( client );
			//agrega si jugador al modelo
			ModeloServidor::get_instancia()->agregar_jugador(cliente_nuevo->get_jugador());
			//le manda el paquete init
			bool es_pacman = cliente_nuevo->get_jugador()->get_personaje()->get_tipo() == Personaje::pacman;
			S_ptr<Paquete> paquete_init(new PaqueteInit(es_pacman,ModeloServidor::get_instancia()->get_mundo().get_mapa_activo()));
			cliente_nuevo->get_escritor().encolar_paquete(paquete_init);
			//si llego a la cantidad minima de clientes, le mando a todos los ya
			//conectados el start
			if( (pool.get_cantidad_clientes() == cant_min_clientes) && (!ya_mando_start) ){
				//espero los 5 segundos que piden
				sleep(5);
				//comienzo el modelo y el hilo avisador
				ModeloServidor::get_instancia()->start(); 
				avisador.start();
				//le mando a todos los clientes el mensje de start
				std::list<Cliente*> lista_clientes = pool.get_clientes();
				std::list<Cliente*>::const_iterator it = lista_clientes.begin();
				while (it != lista_clientes.end()){
					Cliente* Client= *it;
					S_ptr<Paquete> paquete_start(new PaqueteStart(Client->get_id()));
					Client->get_escritor().encolar_paquete(paquete_start);
					++it;
				}
				//setteo el flag para que no lo mande de nuevo
				ya_mando_start = true;
			}
			else{
				//si se agrega un nuevo cliente le mando el mensaje de start
				if( ( pool.get_cantidad_clientes() > cant_min_clientes) &&
					(pool.get_cantidad_clientes() < cant_max_clientes) ){
						S_ptr<Paquete> paquete_start(new PaqueteStart(cliente_nuevo->get_id()));
						cliente_nuevo->get_escritor().encolar_paquete(paquete_start);
					}
			}
			//si la cantidad de maxima, termino de escuchar
			if(pool.get_cantidad_clientes() == cant_max_clientes)
				parar = true;
		}
	} 
	catch( std::runtime_error e ) {
	    // Si es interrumpido.
    }
	avisador.parar();
	avisador.join();
	ModeloServidor::get_instancia()->join();
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

void Servidor::actualizar(Observable * observable, void * param){
	parar = true;
	pthread_kill(this->get_hilo(),Servidor::SENIAL_CANCELAR );
}
