#include "ModeloServidor.h"

ModeloServidor::ModeloServidor() : ModeloCommon(){
/*	//cargar_modelo(); // provisorio
	MundoBasicImp * m = new MundoBasicImp();
	S_ptr<MundoBajoNivel> mundo_default(m);
	this->set_mundo(mundo_default);*/
	this->parar = false;
}

S_ptr<ModeloServidor> ModeloServidor::instancia;

S_ptr<ModeloServidor> ModeloServidor::get_instancia(){
	if( instancia.es_nulo())
		instancia = S_ptr<ModeloServidor>(new ModeloServidor());
	return instancia;
}

ModeloServidor::~ModeloServidor(){
}

void ModeloServidor::agregar_jugador(Jugador * jugador){
	
	Personaje * personaje;
	Jugador * j = jugador;
	//si es el primer jugador, le asigno el personaje de pacman, si no
	//fantasma
	if(jugadores.size() == 0){
  		personaje = new PacMan(j);
      j->agregar_observador(this);
   }
	else
		personaje = new Fantasma(j);
	
	jugador->set_personaje(personaje);
	
   ModeloCommon::agregar_jugador(jugador);
	//this->jugadores.push_back(jugador);
	
}
		
void ModeloServidor::run(){
	//si hay mundo
	if(! mundo.es_nulo()){
		this->termino = false;
		double intervalo_tiempo = 0;
		double hora_actual;
		std::cout << "Soy: " << pthread_self() << "<-- MODELO " << std::endl << std::flush;
		
		Jugador * j;
		//itero por todos los niveles
		//for(int i = 0; i < this->mundo->cantidad_niveles(); i++ ){ 
			//this->set_cambio();//TODO provisorio, no se si va aca o no
			//this->avisar_observadores(NULL); //TODO provisorio, no se si va aca o no
			//lo agrego como observador del mapa, ya que cuando no hay mas quesitos 
			//me avisa
			mundo->get_mapa_activo()->agregar_observador(this);
			//preparo la partida
			this->preparar_partida();
			//mientras este en juego
			while(!this->parar){
				//obtengo la hora actual para evitar el error acumulativo
				hora_actual = Reloj::get_instancia()->get_hora_actual_decimal();
				//
				std::list<Jugador *> lista_jugadores = get_jugadores();
				std::list<Jugador *>::iterator it;
				//recorro todos los jugadores
				for(it = lista_jugadores.begin(); it!= lista_jugadores.end(); it++){
	            j = *it;
               if( j != NULL ){
   					//lo muevo
   					S_ptr<MundoBajoNivel> mun = this->mundo;
   					S_ptr<MapaBajoNivel> map = mun->get_mapa_activo();
   					Personaje* pers = j->get_personaje();
   					map->mover(*j, pers->get_velocidad() * intervalo_tiempo);
   					//reviso las colisiones
   					revisar_colisiones(j ,lista_jugadores);
					}
				}
				//std::cout << "- El jugador "<< j->get_id() << " tiene " << j->get_puntos() << " puntos y esta en ";
				//std::cout << j->get_posicion() <<"\n";
				//j1->colisiono(*j2);
				usleep(2000);
				intervalo_tiempo = (Reloj::get_instancia()->get_hora_actual_decimal() - hora_actual) / 1000;
			}
			//this->mundo->pasar_de_nivel(); // TODO: provisorio, no se si va aca o no
		//}
		//aca se termina, entonces lo avisa y con solo preguntar por esta_terminado()
		//se puede obtener el estado
      std::cout << "ACABA DE TERMIANR EL MODELO!!!!\n";		
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
void ModeloServidor::preparar_partida(){
	this->parar = false;
	
	//para la casa del fantasma y la salida del pacman
	S_ptr<EstructuralUnitario> salida_pacman;
	std::list< S_ptr<EstructuralUnitario> > casa_fantasma;
	
	std::list< S_ptr<EstructuralUnitario> >::iterator it_estucturales;
	std::list< S_ptr<EstructuralUnitario> > lista_estructurales = this->get_mundo().get_mapa_activo()->get_estructurales();
	
	S_ptr<EstructuralUnitario> aux;
	for(it_estucturales = lista_estructurales.begin();
		it_estucturales != lista_estructurales.end();
		++it_estucturales){
		aux = *it_estucturales;
		if( aux->get_tipo() == EstructuralUnitario::Casa_Fantasma )
			casa_fantasma.push_back(*it_estucturales);
		else{
			if( aux->get_tipo() == EstructuralUnitario::Salida_Pacman )
				salida_pacman = *it_estucturales;
		}
	}		
		
	//std::list< S_ptr<Jugador> >::iterator it_jugadores = this->jugadores.begin();
	std::list<Jugador *> lista_jugadores = get_jugadores();
	std::list<Jugador *>::iterator it_jugadores;
	
	it_estucturales = casa_fantasma.begin();
	Jugador * j;
	Posicion p;
	for(it_jugadores = lista_jugadores.begin(); it_jugadores != lista_jugadores.end() ; ++it_jugadores){
		j = *it_jugadores;
		if(j->get_personaje()->get_tipo() == Personaje::pacman){
			p = salida_pacman->get_posicion();
			p.set_x(p.get_x() + 0.5);
			p.set_y(p.get_y() + 0.5);
		}
		else
			if(j->get_personaje()->get_tipo() == Personaje::fantasma){
				aux = *it_estucturales;
				p = aux->get_posicion();
				p.set_x(p.get_x() + 0.5);
				p.set_y(p.get_y() + 0.5);
				if(it_estucturales == casa_fantasma.end() )
					it_estucturales = casa_fantasma.begin();
				else
					it_estucturales++;
			}
			
		j->set_posicion(p);
	}

}
void ModeloServidor::actualizar(Observable * observable, void * param){
   //primero me fijo si el mapa me avisa que ya se comieron todo
	MapaBajoNivel * mapa = dynamic_cast<MapaBajoNivel *>(observable);
	if(mapa != NULL){
		if( mapa->get_comestibles().size() == 0)
			this->parar = true;	
	}
   else{
      //me fijo si me avisa el jugador pacman que se desconecto, entonces
      Jugador * jugador = dynamic_cast<Jugador *>(observable); 
      if(jugador != NULL){
            std::cout << "Me llego un mensaje de un jugador =Z \n";            
            //obtengo el primer jugador de la lista
            std::list<Jugador *>  lista_jugadores = get_jugadores();
            std::list<Jugador *>::iterator it = lista_jugadores.begin();
            
            if( it != lista_jugadores.end() ){
                              
               Personaje * p = new PacMan(*it);
               (*it)->quitar_personaje();
               (*it)->set_personaje(p);
            }
      }
   }
	
}
