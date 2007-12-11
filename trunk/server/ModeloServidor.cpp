#include "ModeloServidor.h"

#include "reloj.h"
#include "PacMan.h"
#include "Fantasma.h"

ModeloServidor::ModeloServidor(){
	//cargar_modelo(); // provisorio
	MundoBasicImp * m = new MundoBasicImp();
	S_ptr<MundoBajoNivel> mundo_default(m);
	this->set_mundo(mundo_default);
	this->parar = false;
}

S_ptr<ModeloServidor> ModeloServidor::instancia;

S_ptr<ModeloServidor> ModeloServidor::get_instancia(){
	if( instancia.es_nulo())
		instancia = S_ptr<ModeloServidor>(new ModeloServidor());
	return instancia;
}

void ModeloServidor::cargar_modelo(){
	
	
	/************parte provisoria cuando esta todo conectado*******************/
	//this->mundo = new MundoBasicImp();
	Jugador *j1 = new Jugador(1);
	Tipo_Jugador j_1(j1);
	this->agregar_jugador(j_1);
	
	Jugador *j2 = new Jugador(2);
	Tipo_Jugador j_2(j2);
	this->agregar_jugador(j_2);
	
	Jugador *j3 = new Jugador(3);
	Tipo_Jugador j_3(j3);
	this->agregar_jugador(j_3);
	/**************************************************************************/
}
void ModeloServidor::set_mundo(S_ptr<MundoBajoNivel> mundo){
	this->mundo = mundo;
	
	//this->mundo->get_mapa_activo().agregar_observador(this);
}
ModeloServidor::~ModeloServidor(){
}

void ModeloServidor::agregar_jugador(Tipo_Jugador jugador){
	
	//if(this->jugadores.size() < this->cant_max_jugadores ){
		S_ptr<Personaje> personaje;
		Jugador * j = &(*jugador);
		//si es el primer jugador, le asigno el personaje de pacman, si no
		//fantasma
		if(jugadores.size() == 0)
			personaje = S_ptr<Personaje>(new PacMan(j));
		else
			personaje = S_ptr<Personaje>(new Fantasma(j));
		jugador->set_personaje(personaje);
		//lo agrego a los jugadores
		this->jugadores.push_back(jugador);
	//}
}
			
void ModeloServidor::run(){
	//si hay mundo
	if(! mundo.es_nulo()){
		this->termino = false;
		double intervalo_tiempo = 0;
		double hora_actual;
		
		std::list<Tipo_Jugador>::iterator it;
		
		Tipo_Jugador j;
		//itero por todos los niveles
		for(int i = 0; i < this->mundo->cantidad_niveles(); i++ ){ 
			this->set_cambio();//TODO provisorio, no se si va aca o no
			this->avisar_observadores(NULL); //TODO provisorio, no se si va aca o no
			//lo agrego como observador del mapa, ya que cuando no hay mas quesitos 
			//me avisa
			mundo->get_mapa_activo()->agregar_observador(this);
			//preparo la partida
			this->preparar_partida();
			//mientras este en juego
			while(!this->parar){
				//obtengo la hora actual para evitar el error acumulativo
				hora_actual = Reloj::get_instancia()->get_hora_actual_decimal();
				//recorro todos los jugadores
				for(it = jugadores.begin(); it!= jugadores.end(); it++){
					j = *it;
					//lo muevo
					(this->mundo->get_mapa_activo())->mover(*j, j->get_personaje()->get_velocidad() * intervalo_tiempo);
					//reviso las colisiones
					revisar_colisiones(j);
					
				}
				//std::cout << "- El jugador "<< j->get_id() << " tiene " << j->get_puntos() << " puntos y esta en ";
				//std::cout << j->get_posicion() <<"\n";
				//j1->colisiono(*j2);
				usleep(2000);
				intervalo_tiempo = (Reloj::get_instancia()->get_hora_actual_decimal() - hora_actual) / 1000;
			}
			this->mundo->pasar_de_nivel(); // TODO: provisorio, no se si va aca o no
		}
		//aca se termina, entonces lo avisa y con solo preguntar por esta_terminado()
		//se puede obtener el estado
		this->termino = true;
		this->set_cambio();
		this->avisar_observadores(NULL);
	}
}


void ModeloServidor::revisar_colisiones(S_ptr<Jugador>& j){
	std::list<Tipo_Jugador>::iterator it;
	 
	Tipo_Jugador j2;
	
	for(it = jugadores.begin(); it!= jugadores.end(); it++){
		j2 = *it;
		j->colisiono(&(*j2));
	}	
}

const std::list<S_ptr<Jugador> >& ModeloServidor::get_jugadores(){
	return this->jugadores;
}
S_ptr<Jugador> ModeloServidor::get_jugador(int id){
	
	std::list< S_ptr<Jugador> >::iterator it_jugadores;
	
	S_ptr<Jugador> resultado_busqueda;
	
	for(it_jugadores = this->jugadores.begin(); 
		it_jugadores != this->jugadores.end(); it_jugadores++){
		
		if( (*it_jugadores)->get_id() == id)
			resultado_busqueda = *it_jugadores;
	}
	return resultado_busqueda;
}
	
MundoBajoNivel& ModeloServidor::get_mundo(){
	return *this->mundo;
}
void ModeloServidor::actualizar(Observable * observable, void * param){
	this->parar = true;
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
		
	std::list< S_ptr<Jugador> >::iterator it_jugadores = this->jugadores.begin();
	
	it_estucturales = casa_fantasma.begin();
	S_ptr<Jugador> j;
	Posicion p;
	for(it_jugadores = this->jugadores.begin(); it_jugadores != this->jugadores.end() ; ++it_jugadores){
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
bool ModeloServidor::esta_terminado(){
	return this->termino;
}
void ModeloServidor::set_cargado(){
	this->set_cambio();
	this->avisar_observadores(NULL);
}
