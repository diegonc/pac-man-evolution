#include "Modelo.h"

/////////////////////////////////
#include "PacMan.h"
#include "Fantasma.h"

/////////////////////////////////

Modelo::Modelo(std::string ruta_mundo){
	cargar_modelo(ruta_mundo);
	
}

void Modelo::cargar_modelo(std::string ruta_mundo){
	this->mundo = new MundoBasicImp(ruta_mundo);
	
	/**************************************************************************/
	S_ptr<Personaje> pacman(new Fantasma);
	//S_ptr<Personaje> fantasmita(new Fantasma);
	
	Jugador *j1 = new Jugador(1, pacman);
	S_ptr<Jugador> j_1(j1);
	Posicion p(0,0);
	j1->set_posicion(p);
	
	/*Jugador *j2 = new Jugador(2, fantasmita);
	S_ptr<Jugador> j_2(j2);
	Posicion p2(3,0);
	j1->set_posicion(p2);*/
		
	this->agregar_jugador(j_1);
	///this->agregar_jugador(j_2);
	
	/**************************************************************************/
	/*TODO TRUCHAR OPERACIONES Y DESPUES REEMPLAZAR POR UN PARSER*/
}

Modelo::~Modelo(){
	delete this->mundo;
}

void Modelo::agregar_jugador(Tipo_Jugador jugador){
	this->jugadores.push_back(jugador);
}
			
void Modelo::run(){
	std::list<Tipo_Jugador>::iterator it = jugadores.begin();
	
	Tipo_Jugador j = *it;
	for(int i = 0; i < 10; i++){
		(this->mundo->get_mapa_activo()).mover(*j,Direccion::Oeste, 0.5);
		std::cout << "- El jugador tiene " << j->get_puntos() << " puntos y esta en ";
		std::cout << j->get_posicion() <<"\n";
		sleep(1);
	}
	
	
}
