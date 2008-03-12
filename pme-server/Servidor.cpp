#include "Servidor.h"

#include "PaqueteInit.h"
#include "PaqueteStart.h"
#include "PaqueteStop.h"
#include "PaqueteQuit.h"
#include <server/EscritorCliente.h>

#define _DEFAULT_CANT_MIN	2
#define _DEFAULT_CANT_MAX	10
#define _DEMORA_INICIO_PARTIDA 5 //demora en segs

const int Servidor::SENIAL_CANCELAR = SIGUSR1;	

#include <unistd.h>


void Servidor::manejador_signal(int num_signal){

	switch(num_signal){
		case Servidor::SENIAL_CANCELAR: 
         //std::cout << "entro a SIGUSR1" << std::endl << std::flush;
      break;
		
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
   delete (this->avisador);
}
void Servidor::run(){
	
	this->ejecutando = true; //El servidor arranca a ejecutarse
   this->ya_mando_start = false; //Controla si se mando la primera vez la partida

	//Pone al socket a escuchar clientes
	socket->escuchar();

   //Arranco al modelo
   ModeloServidor::get_instancia()->start();

   //Inicio el primer nivel
   this->iniciar_nivel();
	
   //Mientras el servidor se esta ejecutando
	while( this->esta_ejecutando() ) {
		
      //Acepto un cliente nuevo
      Cliente* cliente_nuevo = this->aceptar_nuevo_cliente();
     
      //Si se pudo aceptar continuo con el proceso, sino intento aceptar nuevamente
      if (cliente_nuevo != NULL) {
			//si llego a la cantidad minima de clientes, le mando a todos los ya
			//conectados el start
			if( (pool.get_cantidad_clientes() >= cant_min_clientes) && (!ya_mando_start) ){
            //Proceso el nuevo nivel
            this->procesar_nivel();
			}
			else{
				//Si se esta agregando un nuevo cliente y no se llego a la cantidad maxima, le envio un start
				if ((pool.get_cantidad_clientes() <= cant_max_clientes) 
				    && (pool.get_cantidad_clientes() >= cant_min_clientes) ) 
						this->mandar_start(cliente_nuevo);
				//Cuando se llega a la cantidad maxima trabo al servidor para que rebote a los clientes q se intenten   
            //conectar
            if (pool.get_cantidad_clientes() == cant_max_clientes)
                  this->llave_max_jugadores->esperar_activacion();
		   }
      }
      //Si tiene que cambiar de nivel lo hace
      if (this->debo_cambiar_nivel)
         this->cambiar_nivel();
   }
   //Cuando termina el servidor hago join del modelo
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
   std::cout << "Cerrando Servidor" << std::endl << std::flush;
   this->finalizar_nivel();
   //Mando un paquete de quit a todos los clientes
   this->mandar_quit();
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
   std::cout << "Inicializando Servidor" << std::endl << std::flush;   
   //setteo las propieades de la senial para cortar el accept
	set_propiedades_signal(Servidor::SENIAL_CANCELAR);
	//asigno por defecto las cantidades minimas y maximas de jugadores
	this->cant_max_clientes = _DEFAULT_CANT_MAX;
	this->cant_min_clientes = _DEFAULT_CANT_MIN;
   //Pongo como que no se esta ejecutando
   this->ejecutando = false;
   this->debo_cambiar_nivel = false;
	//Agrego al servidor como observador del pool de clientes
	this->pool.agregar_observador(this);
	MessageDispatcher::get_instancia()->set_PoolClientes(&pool);
   //Agrego al servidor como observador del modelo
   ModeloServidor::get_instancia()->agregar_observador(this);
   //Creo el avisador de novedades
   this->avisador = new AvisadorNovedades(&(this->pool));
}

Cliente* Servidor::aceptar_nuevo_cliente(){
      try {
         	std::cout << "aceptando cliente" << std::endl << std::flush;         
         	//Acepta un cliente
			Socket_Cliente* client = socket->aceptar();
        	 std::cout << "cliente aceptado" << std::endl << std::flush;    
			//lo agrega a la pileta de clientes
			Cliente * cliente_nuevo = pool.lanzar_cliente( client );
			//Agrega el jugador al modelo
			ModeloServidor::get_instancia()->agregar_jugador(cliente_nuevo->get_jugador());
			//Le manda el paquete init
         	this->mandar_init(cliente_nuevo);
		  	if ((!this->avisador->corriendo()) && (ya_mando_start)){
				this->avisador->start();
			}

			if(ya_mando_start){
				this->avisador->mandar_todo();
			}			
         return cliente_nuevo; //Devuelvo el cliente creado
      } catch (std::runtime_error) {
          std::cout << "cliente falla" << std::endl << std::flush;          
         //Si falla el aceptar devuelvo un cliente nulo
         return NULL;
      }
}

void Servidor::iniciar_nivel(){
   //Pauso al modelo
   ModeloServidor::get_instancia()->pausar();
   //Pongo al avisador como observador del mapa actual
	ModeloServidor::get_instancia()->get_mundo().get_mapa_activo()->agregar_observador(this->avisador);
   //Mando los inits a los clientes que tengo actualmente conectados
	std::list<Cliente*> lista_clientes = pool.get_clientes();
	std::list<Cliente*>::const_iterator it = lista_clientes.begin();
	while (it != lista_clientes.end()){
		Cliente* Client= *it;
		this->mandar_init(Client);
		++it;
	}
   std::cout << "nivel iniciado" << std::endl << std::flush;
}

void Servidor::procesar_nivel(){
   std::cout << "procesando nivel" << std::endl << std::flush;   
   //espero los segundos de demora para el inicio de la partida
	sleep(_DEMORA_INICIO_PARTIDA);
   //despauso el modelo
	ModeloServidor::get_instancia()->despausar(); 
   std::cout << "destrabe el modelo" << std::endl << std::flush;
   //le mando a todos los clientes el mensje de start
	std::list<Cliente*> lista_clientes = pool.get_clientes();
	std::list<Cliente*>::const_iterator it = lista_clientes.begin();
	while (it != lista_clientes.end()){
		Cliente* Client= *it;
		this->mandar_start(Client);
		++it;
	}
   //Arranco el avisador de novedades, para empezar a mandar status
   this->avisador->start();
   //setteo el flag para que no lo mande de nuevo
	ya_mando_start = true;
}

void Servidor::finalizar_nivel(){
   std::cout << "finalizando nivel" << std::endl << std::flush;
   //Cuando termina un nivel freno al avisador y le hago join
	if (this->avisador->corriendo()){
		this->avisador->parar();
		this->avisador->join();
	}
   this->ya_mando_start = false;
}

void Servidor::cambiar_nivel(){
   std::cout << "cambiando de nivel" << std::endl << std::flush;
   //Finalizo el nivel anterior
   this->finalizar_nivel();
   this->avisador->borrar_novedades_acumuladas();
   //Mando a los clientes que el pacman gano el nivel
   this->mandar_stop(PaqueteStop::pacman_gano);   
   //Inicio el nuevo nivel
   this->iniciar_nivel();
   //Lo proceso
   this->procesar_nivel();
   this->debo_cambiar_nivel = false;
}

void Servidor::mandar_init(Cliente* cliente){
   //Si es pacman le manda que es pacman, sino que es fantasma
	bool es_pacman = cliente->get_jugador()->get_personaje()->get_tipo() == Personaje::pacman;
	std::cout << "Mandando paquete init a: " << cliente->get_id() << std::endl << std::flush;  
   S_ptr<Paquete> paquete_init(new PaqueteInit(es_pacman,ModeloServidor::get_instancia()->get_mundo().get_mapa_activo()));
   //Encolo el paquete para mandar
   cliente->get_escritor().encolar_paquete(paquete_init);
}

void Servidor::mandar_start(Cliente* cliente){
     //Creo un paquete start y lo encolo en el escritor del cliente
      std::cout << "Mandando paquete start a: " << cliente->get_id() << std::endl << std::flush;
   	S_ptr<Paquete> paquete_start(new PaqueteStart(cliente->get_id()));
	   cliente->get_escritor().encolar_paquete(paquete_start);
}

void Servidor::mandar_stop(const char razon){
	//Busco al pacman entre todos los clientes
	bool encontrado = false;
	std::list<Cliente*> lista_clientes = pool.get_clientes();
	std::list<Cliente*>::const_iterator it = lista_clientes.begin();
	Cliente* cliente = NULL;
	while ((it != lista_clientes.end()) && (!encontrado)){
		cliente = *it;
		if (cliente->get_jugador()->get_personaje()->get_tipo() == Personaje::pacman)
			encontrado = true;
		++it;
	}
	int puntaje = 0; //puntaje del pacman
	if (encontrado) puntaje = cliente->get_jugador()->get_puntos();
	//creo el paquete stop con el puntaje obtenido y se lo mando a todos los clientes
	S_ptr<Paquete> paquete_stop(new PaqueteStop(razon, puntaje));
	pool.mandar_mensaje_todos(paquete_stop);
}

void Servidor::mandar_quit(){
	//creo el paquete quit y se lo mando a todos los clientes
	S_ptr<Paquete> paquete_quit(new PaqueteQuit());
	pool.mandar_mensaje_todos(paquete_quit);
}

void Servidor::actualizar(Observable * observable, void * param){
	//Intento castear como pool de clientes	
	ClientPool* client_pool = dynamic_cast<ClientPool*> (observable);
	//Si se pudo castear, es porque el client pool me aviso que se conecto o desconecto un cliente
	if (client_pool != NULL){
		//Obtengo el parametro como cliente
		Cliente* cliente = (Cliente*) (param);
      //Me fijo si el cliente se conecto o se desconecto
      //Si esta en el pool es porque se conecto, de lo contrario se desconecto
      if (client_pool->buscar_cliente(cliente->get_id())){
         std::cout << "Se agrego el cliente: " << cliente->get_id() << std::cout << std::endl;
         //Si la cantidad de clientes es mayor a la minima, y el modelo esta pausado, lo despauso
      	if ((client_pool->get_cantidad_clientes() >= cant_min_clientes) 
             && (ModeloServidor::get_instancia()->esta_pausado())){
			   std::cout << "reiniciar partida antes" << std::endl << std::flush;
               ModeloServidor::get_instancia()->reiniciar_partida(); 
			   std::cout << "reiniciar partida desp" << std::endl << std::flush;				 
               ModeloServidor::get_instancia()->despausar();
         }
      } else {
         //Si la cantidad de clientes es menor a la minima, pauso el modelo y mando un stop indicando lo sucedido
      	if (client_pool->get_cantidad_clientes() < cant_min_clientes){
            ModeloServidor::get_instancia()->pausar();
			if (this->avisador->corriendo()){
				this->avisador->parar();
				this->avisador->join();
			}
            this->mandar_stop(PaqueteStop::cant_insuficiente);
         }
      	//Si el cliente que se desconecto es el pac-man, aviso a los demas clientes y reinicio el nivel
      	if (cliente->get_jugador()->get_personaje()->get_tipo() == Personaje::pacman) {
            this->mandar_stop(PaqueteStop::pacman_desconecto);
            ModeloServidor::get_instancia()->reiniciar_partida();
         }
      }
	} else {
		//Intento castear como modelo del servidor
		ModeloServidor* modelo = dynamic_cast<ModeloServidor*>(observable);
		//Si pudo castear, es porque el modelo me avisa que termino el nivel o el juego
		if (modelo != NULL) {
			//Le pregunto al modelo si termino el juego
			if (modelo->esta_terminado())
				//Si termino el juego, finalizo el servidor
				this->finalizar_servidor();
			else { //Sino, es porque termino un nivel, asi q debo cambiar de nivel
            this->debo_cambiar_nivel = true;
            //Destrabo al server
            //Si estaba esperando evento lo destrabo
            if (this->llave_max_jugadores->esta_esperando())
               this->llave_max_jugadores->lanzar_evento();
            //Mando una senial para destrabarlo del accept, si no estaba aceptando la señal se ignora
            pthread_kill(this->get_hilo(), Servidor::SENIAL_CANCELAR);
         }		
      }
	}
}
