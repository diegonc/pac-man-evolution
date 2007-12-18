#include "ModeloServidor.h"

ModeloServidor::ModeloServidor() : ModeloCommon(){
   this->nivel_terminado = false;
   this->pausado = false;
   this->evento_despausar = new Evento();
}

S_ptr<ModeloServidor> ModeloServidor::instancia;

S_ptr<ModeloServidor> ModeloServidor::get_instancia(){
	if( instancia.es_nulo())
		instancia = S_ptr<ModeloServidor>(new ModeloServidor());
	return instancia;
}

ModeloServidor::~ModeloServidor(){
   delete(this->evento_despausar);
}

void ModeloServidor::agregar_jugador(Jugador * jugador){
	
	Personaje * personaje;
	Jugador * j = jugador;
	//si es el primer jugador, le asigno el personaje de pacman, si no
	//fantasma
	if(jugadores.size() == 0)
  		personaje = new PacMan(j);
	else
		personaje = new Fantasma(j);
	
	jugador->set_personaje(personaje);
	
   ModeloCommon::agregar_jugador(jugador);
	
}
		
void ModeloServidor::run(){
	//si hay mundo
	if(! mundo.es_nulo()){
		this->termino = false;
		double intervalo_tiempo = 0;
		double hora_actual;
		
		Jugador * j;
		//itero por todos los niveles
		for(int i = 0; i < this->mundo->cantidad_niveles(); i++ ){ 
			//lo agrego como observador del mapa, ya que cuando no hay mas quesitos 
			//me avisa
			mundo->get_mapa_activo()->agregar_observador(this);
			//preparo la partida
			this->preparar_partida();
         this->nivel_terminado = false;
			//mientras este en juego
			while(!this->nivel_terminado){
            //Me fijo si se efectuo una pausa, y en este caso realizo una espera pasiva
            if (this->pausado)            
               this->evento_despausar->esperar_activacion();				
            //obtengo la hora actual para evitar el error acumulativo
				hora_actual = Reloj::get_instancia()->get_hora_actual_decimal();
				std::list<Jugador *> lista_jugadores = get_jugadores();
				std::list<Jugador *>::iterator it;
				//recorro todos los jugadores
				for(it = lista_jugadores.begin(); it!= lista_jugadores.end(); it++){
	            j = *it;
               if( j != NULL ){
   					//lo muevo
   					S_ptr<MundoBajoNivel> mun = this->mundo;
   					MapaBajoNivel* map = mun->get_mapa_activo();
   					Personaje* pers = j->get_personaje();
   					map->mover(*j, pers->get_velocidad() * intervalo_tiempo);
   					//reviso las colisiones
   					revisar_colisiones(j ,lista_jugadores);
					}
				}
				usleep(2000);
				intervalo_tiempo = (Reloj::get_instancia()->get_hora_actual_decimal() - hora_actual) / 1000;
			}
			this->mundo->pasar_de_nivel();
         //Aviso a los observadores del cambio de nivel
         this->set_cambio();
			this->avisar_observadores(NULL);
		}
		//aca se termina, entonces lo avisa y con solo preguntar por esta_terminado()
		//se puede obtener el estado
      this->termino = true;
		this->set_cambio();
		this->avisar_observadores(NULL);
	}
}


void ModeloServidor::revisar_colisiones(Jugador * j, std::list<Jugador *>& lista_jugadores){
	std::list<Jugador *>::iterator it;
	 
	Jugador * j2;
	
	for(it = lista_jugadores.begin(); it != lista_jugadores.end(); it++){
      j2 = *it;
		j->colisiono(j2);
	}	
}

void ModeloServidor::reiniciar_partida(){
  
   bool hay_pacman = false;   
   //obtengo el primer jugador de la lista
   std::list<Jugador *>  lista_jugadores = get_jugadores();
   std::list<Jugador *>::iterator it = lista_jugadores.begin();
   

   //me fijo que haya jugadores
   if(lista_jugadores.size() != 0 ){
      //busco si hay pacman si no despues se lo asigno a otro      
      do{
         if( (*it)->get_personaje()->get_tipo() == Personaje::pacman ){
            hay_pacman = true;
         }
         ++it;
      }while( (it != lista_jugadores.end() ) && (!hay_pacman) );
      //si no habia pacman, se lo asigno al primer personaje de la lista      
      if(!hay_pacman){
            it = lista_jugadores.begin();            

            Personaje * p = new PacMan(*it);
            Jugador * j = *it;
            j->quitar_personaje();
            j->set_personaje(p);
      }
   }
   preparar_partida();
}

void ModeloServidor::actualizar(Observable * observable, void * param){
   //Me fijo si el mapa me avisa que no quedan mas comestibles para terminar el desarrollo del nivel actual
	MapaBajoNivel * mapa = dynamic_cast<MapaBajoNivel *>(observable);
	if(mapa != NULL){
		if( mapa->get_comestibles().size() == 0)
			this->nivel_terminado = true;	
	}
}

void ModeloServidor::pausar(){
   if (!this->esta_pausado())
      this->pausado = true;
}

void ModeloServidor::despausar(){
   if (this->esta_pausado()){
      this->pausado = false;
      this->evento_despausar->lanzar_evento();
   }
}

bool ModeloServidor::esta_pausado(){
   return this->pausado;
}


