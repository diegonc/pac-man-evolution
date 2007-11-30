#include "ModeloServidor.h"

/////////////////////////////////
#include "PacMan.h"
#include "Fantasma.h"

/////////////////////////////////

ModeloServidor::ModeloServidor(std::string ruta_mundo){
	cargar_modelo(ruta_mundo);
	
}

void ModeloServidor::cargar_modelo(std::string ruta_mundo){
	this->parar = false;
	
	this->mundo = new MundoBasicImp(ruta_mundo);
	
	/**************************************************************************/
	
	Jugador *j1 = new Jugador(1);
	Tipo_Jugador j_1(j1);
	S_ptr<Personaje> pacman(new PacMan(j1));
	j_1->set_personaje(pacman);
	Posicion p(0.5,0.5);
	j_1->set_posicion(p);
	
	Jugador *j2 = new Jugador(2);
	Tipo_Jugador j_2(j2);
	S_ptr<Personaje> fantasmita(new Fantasma(j2));
	j_2->set_personaje(fantasmita);
	Posicion p2(3.5,0.5);
	j_2->set_posicion(p2);
	
	this->agregar_jugador(j_1);
	this->agregar_jugador(j_2);
		
	/**************************************************************************/
	/*TODO TRUCHAR OPERACIONES Y DESPUES REEMPLAZAR POR UN PARSER*/
	
	this->mundo->get_mapa_activo().agregar_observador(this);
}

ModeloServidor::~ModeloServidor(){
	delete this->mundo;
}

void ModeloServidor::agregar_jugador(Tipo_Jugador jugador){
	this->jugadores.push_back(jugador);
}
			
void ModeloServidor::run(){
	std::list<Tipo_Jugador>::iterator it;
	
	Tipo_Jugador j;
	
	for(int i = 0; this->mundo->cantidad_niveles(); i++ ){ 
		preparar_partida();
		
		while(!this->parar){
			for(it = jugadores.begin(); it!= jugadores.end(); it++){
				j = *it;
				(this->mundo->get_mapa_activo()).mover(*j, j->get_personaje()->get_velocidad() * 0.002);
				revisar_colisiones(j);
			}
			//std::cout << "- El jugador tiene " << j->get_puntos() << " puntos y esta en ";
			//std::cout << j->get_posicion() <<"\n";
			//j1->colisiono(*j2);
			usleep(2000);
		}
	}
	std::cout << "termino esta caca\n";
			
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

}
