#include "Servidor.h"

#include "PaqueteInit.h"
#include "PaqueteStart.h"
#include "../common/EscritorCliente.h"
#include "AvisadorNovedades.h"

#define _DEFAULT_CANT_MIN	2
#define _DEFAULT_CANT_MAX	10
#define _DEMORA_INICIO_PARTIDA 5 //demora en segs

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
		sigaction(id_signal,&this->accion_signal, NULL);
	
}
Servidor::Servidor(std::string &direccion, unsigned short int puerto)
{
	try{
		//creo el socket del servidor
		this->socket = new Socket_Server();
		//lo bindeo
		this->socket->bind_socket(direccion, puerto);
		//Inicializo el servidor
      this->inicializar();
      //Creo la llave para max jugadores
      this->llave_max_jugadores = new Evento();
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
      //creo el socket del servidor
		this->socket = new Socket_Server();
      //lo bindeo
		this->socket->bind_socket(puerto);
      //Inicializo el servidor
      this->inicializar();
      //Creo la llave para max jugadores
      this->llave_max_jugadores = new Evento();
	}
	catch (std::runtime_error &e){
		//si hubo error borro el socket que seguro se creo
		delete this->socket; 
		throw e;	
	}
}
Servidor::~Servidor()
{
	if( socket )
		delete socket;
   delete (this->llave_max_jugadores);
}
void Servidor::run(){

	AvisadorNovedades avisador(&this->pool);
	
	this->ejecutando = true; //El servidor arranca a ejecutarse
	bool ya_mando_start = false; //Controla si se mando la primera vez la partida
	
	ModeloServidor::get_instancia()->get_mundo().get_mapa_activo()->agregar_observador(&avisador);
	//Pone al socket a escuchar clientes
	socket->escuchar();
		
   //Mientras el servidor se esta ejecutando
	while( this->esta_ejecutando() ) {
		
      //Acepto un cliente nuevo
      Cliente* cliente_nuevo = this->aceptar_nuevo_cliente();
      //Si se pudo aceptar continuo con el proceso, sino intento aceptar nuevamente
      if (cliente_nuevo != NULL) {
			//si llego a la cantidad minima de clientes, le mando a todos los ya
			//conectados el start
			if( (pool.get_cantidad_clientes() == cant_min_clientes) && (!ya_mando_start) ){
				
            //Inicio la partida
            this->iniciar_partida();

            //Arranco el avisador de novedades, para empezar a mandar status
            avisador.start();

				//setteo el flag para que no lo mande de nuevo
				ya_mando_start = true;
			}
			else{
				//Si se esta agregando un nuevo cliente y no se llego a la cantidad maxima, le envio un start
				if (pool.get_cantidad_clientes() <= cant_max_clientes) 
						this->mandar_start(cliente_nuevo);
				//Cuando se llega a la cantidad maxima trabo al servidor para que rebote a los clientes q se intenten   
            //conectar
            if (pool.get_cantidad_clientes() == cant_max_clientes)
                  this->llave_max_jugadores->esperar_activacion();
		   }
      }
   }

   //Cuando termina el servidor freno al avisador y le hago join, y hago join con el modelo.
	avisador.parar();
	avisador.join();
	ModeloServidor::get_instancia()->join();
   //Hago join con todos los clientes
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

void Servidor::finalizar_servidor(){
   //Le digo que se deja de ejecutar
   this->ejecutando = false;
   //Si estaba esperando evento lo destrabo
   if (this->llave_max_jugadores->esta_esperando())
      this->llave_max_jugadores->lanzar_evento();
   //Mando una senial para destrabarlo del accept, si no estaba aceptando la señal se ignora
   this->thread_kill(Servidor::SENIAL_CANCELAR);
}

bool Servidor::esta_ejecutando(){
   return this->ejecutando;
}

void Servidor::inicializar(){
   	//setteo las propieaddes de la senial para cortar el accept
	set_propiedades_signal(Servidor::SENIAL_CANCELAR);
	//asigno por defecto las cantidades minimas y maximas de jugadores
	this->cant_max_clientes = _DEFAULT_CANT_MAX;
	this->cant_min_clientes = _DEFAULT_CANT_MIN;
   	//Pongo como que no se esta ejecutando
   	this->ejecutando = false;
	//Agrego al servidor como observador del pool de clientes
	this->pool.agregar_observador(this);
}

Cliente* Servidor::aceptar_nuevo_cliente(){
      try {         
         //Acepta un cliente
			Socket_Cliente* client = socket->aceptar();
			//lo agrega a la pileta de clientes
			Cliente * cliente_nuevo = pool.lanzar_cliente( client );
			//Agrega el jugador al modelo
			ModeloServidor::get_instancia()->agregar_jugador(cliente_nuevo->get_jugador());
			//Le manda el paquete init
         //Si es pacman le manda que es pacman, sino que es fantasma
			bool es_pacman = cliente_nuevo->get_jugador()->get_personaje()->get_tipo() == Personaje::pacman;
			S_ptr<Paquete> paquete_init(new PaqueteInit(es_pacman,ModeloServidor::get_instancia()->get_mundo().get_mapa_activo()));
         //Encolo el paquete para mandar
			cliente_nuevo->get_escritor().encolar_paquete(paquete_init);
         return cliente_nuevo; //Devuelvo el cliente creado
      } catch (std::runtime_error) {
         //Si falla el aceptar devuelvo un cliente nulo
         return NULL;
      }
}

void Servidor::iniciar_partida(){
	//espero los segundos de demora para el inicio de la partida
	sleep(_DEMORA_INICIO_PARTIDA);
	//comienzo el modelo
	ModeloServidor::get_instancia()->start(); 
	//le mando a todos los clientes el mensje de start
	std::list<Cliente*> lista_clientes = pool.get_clientes();
	std::list<Cliente*>::const_iterator it = lista_clientes.begin();
	while (it != lista_clientes.end()){
		Cliente* Client= *it;
		this->mandar_start(Client);
		++it;
	}
}

void Servidor::mandar_start(Cliente* cliente){
      //Creo un paquete start y lo encolo en el escritor del cliente
   	S_ptr<Paquete> paquete_start(new PaqueteStart(cliente->get_id()));
	   cliente->get_escritor().encolar_paquete(paquete_start);
}

void Servidor::actualizar(Observable * observable, void * param){
	//Intento castear como pool de clientes	
	ClientPool* client_pool = dynamic_cast<ClientPool*> (observable);
	//Si se pudo castear, es porque el client pool me aviso que se desconecto un cliente
	if (client_pool != NULL){
		//Obtengo el parametro como cliente
		Cliente* cliente = (Cliente*) (param);
		//Si la cantidad de clientes es menor a la minima, freno el modelo
		if (client_pool->get_cantidad_clientes() < cant_min_clientes)
			;//PARAR MODELO
		//Si el cliente que se desconecto es el pac-man, aviso a los demas clientes y reinicio el nivel
		if (cliente->get_jugador()->get_personaje()->get_tipo() == Personaje::pacman)
			;//AVISAR CLIENTES, REINICIAR NIVEL
	} else {
		//Intento castear como modelo del servidor
		ModeloServidor* modelo = dynamic_cast<ModeloServidor*>(observable);
		//Si pudo castear, es porque el modelo me avisa que termino el nivel o el juego
		if (modelo != NULL) {
			//Le pregunto al modelo si termino el juego
			/*if (modelo->termino_juego())
				//Si termino el juego, finalizo el servidor
				this->finalizar_servidor();
			else //Sino, es porque termino un nivel
				//AVISAR CAMBIO NIVEL */
		}
	}
}

