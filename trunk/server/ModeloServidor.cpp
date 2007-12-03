#include "ModeloServidor.h"

/////////////////////////////////
#include "PacMan.h"
#include "Fantasma.h"

/////////////////////////////////

ModeloServidor::ModeloServidor(){
	cargar_modelo();
	
}

void ModeloServidor::cargar_modelo(){
	this->parar = false;
	
	//this->mundo = new MundoBasicImp();
	
	/**************************************************************************/
	
	Jugador *j1 = new Jugador(1);
	Tipo_Jugador j_1(j1);
	Posicion p(0.5,0.5);
	j_1->set_posicion(p);
	this->agregar_jugador(j_1);
	
	/*Jugador *j2 = new Jugador(2);
	Tipo_Jugador j_2(j2);
	Posicion p2(3.5,0.5);
	j_2->set_posicion(p2);
	this->agregar_jugador(j_2);
	*/
	/**************************************************************************/
	/*TODO TRUCHAR OPERACIONES Y DESPUES REEMPLAZAR POR UN PARSER*/
	
	
}
void ModeloServidor::set_mundo(S_ptr<MundoBajoNivel> mundo){
	this->mundo = mundo;
	this->mundo->get_mapa_activo().agregar_observador(this);
}
ModeloServidor::~ModeloServidor(){
}

void ModeloServidor::agregar_jugador(Tipo_Jugador jugador){
	S_ptr<Personaje> personaje;
	
	Jugador * j = &(*jugador);
	if(jugadores.size() == 0)
		personaje = S_ptr<Personaje>(new PacMan(j));
	else
		personaje = S_ptr<Personaje>(new Fantasma(j));
	jugador->set_personaje(personaje);
	
	this->jugadores.push_back(jugador);
}
			
void ModeloServidor::run(){
	if(! mundo.es_nulo() ){
		std::list<Tipo_Jugador>::iterator it;
		
		Tipo_Jugador j;
		
		std::cout<< "Hay " << this->mundo->cantidad_niveles() << " niveles\n";
		for(int i = 0; i < this->mundo->cantidad_niveles(); i++ ){ 
			mundo->get_mapa_activo().agregar_observador(this);
			preparar_partida();
			while(!this->parar){
				for(it = jugadores.begin(); it!= jugadores.end(); it++){
					j = *it;
					(this->mundo->get_mapa_activo()).mover(*j, j->get_personaje()->get_velocidad() * 0.002);
					revisar_colisiones(j);
				}
				//std::cout << "- El jugador "<< j->get_id() << " tiene " << j->get_puntos() << " puntos y esta en ";
				//std::cout << j->get_posicion() <<"\n";
				//j1->colisiono(*j2);
				usleep(2000);
				
			}
			
		}
	}
}

void ModeloServidor::revisar_colisiones(S_ptr<Jugador>& j){
	std::list<Tipo_Jugador>::iterator it;
	
	Tipo_Jugador j2;
	for(it = jugadores.begin(); it!= jugadores.end(); it++){
		j2 = *it;
		j->colisiono(*j2);
		
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
	/*
	//para la casa del fantasma y la salida del pacman
	S_ptr<EstructuralUnitario> salida_pacman;
	std::list< S_ptr<EstructuralUnitario> > casa_fantasma;
	
	std::list< S_ptr<EstructuralUnitario> >::iterator it_estucturales;
	
	
	S_ptr<EstructuralUnitario> aux;
	for(it_estucturales = this->get_mundo().get_mapa_activo().get_estructurales().begin();
		it_estucturales != this->get_mundo().get_mapa_activo().get_estructurales().end();
		++it_estucturales){
			
		aux = *it_estucturales;
		if( aux->es_casa_fantasma() )
			casa_fantasma.push_back(*it_estucturales);
		else{
			if(aux->es_salida_pacman() )
				salida_pacman = *it_estucturales;
		}
	}		
	*/
	/*
	std::list< S_ptr<Jugador> >::iterator it_jugadores = this->jugadores.begin();
	
	it_estucturales = casa_fantasma.begin();
	S_ptr<Jugador> j;
	for(it_jugadores = this->jugadores.begin(); it_jugadores != this->jugadores.end() ; ++it_jugadores){
		j = *it_jugadores;
		if(j->get_personaje()->get_tipo() == Personaje::pacman){
			Posicion p = salida_pacman->get_posicion();
			p.set_x(p.get_x() + 0.5);
			p.set_y(p.get_y() + 0.5);
			j->set_posicion(p);
		}
		else
			if(j->get_personaje()->get_tipo() == Personaje::fantasma){
				aux = *it_estucturales;
				Posicion p = aux->get_posicion();
				p.set_x(p.get_x() + 0.5);
				p.set_y(p.get_y() + 0.5);
				if(it_estucturales == casa_fantasma.end() )
					it_estucturales = casa_fantasma.begin();
			}
	}*/
}
