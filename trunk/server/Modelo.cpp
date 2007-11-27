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
	
	Jugador *j1 = new Jugador(1);
	S_ptr<Jugador> j_1(j1);
	S_ptr<Personaje> pacman(new PacMan(j1));
	j_1->set_personaje(pacman);
	Posicion p(0,0);
	j_1->set_posicion(p);
	
	Jugador *j2 = new Jugador(1);
	S_ptr<Jugador> j_2(j2);
	S_ptr<Personaje> fantasmita(new Fantasma(j2));
	j_2->set_personaje(pacman);
	Posicion p2(0,3);
	j_2->set_posicion(p2);
	
	this->agregar_jugador(j_1);
	this->agregar_jugador(j_2);
	
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
	
	Tipo_Jugador j1 = *it;
	it++;
	Tipo_Jugador j2 = *it;
	//for(int i = 0; i < 5; i++){
		(this->mundo->get_mapa_activo()).mover(*j1,Direccion::Oeste, 0.5);
		std::cout << "- El jugador 1 tiene " << j1->get_puntos() << " puntos y esta en ";
		std::cout << j1->get_posicion() <<"\n";
		sleep(1);
	//}
	j1->colisiono(*j2);
	
	
	(this->mundo->get_mapa_activo()).mover(*j2,Direccion::Este, 0.5);
	std::cout << "- El jugador 2 tiene " << j2->get_puntos() << " puntos y esta en ";
	std::cout << j2->get_posicion() <<"\n";
	sleep(1);
	
	j2->colisiono(*j1);
	
	(this->mundo->get_mapa_activo()).mover(*j1,Direccion::Oeste, 0.5);
	std::cout << "- El jugador 1 tiene " << j1->get_puntos() << " puntos y esta en ";
	std::cout << j1->get_posicion() <<"\n";
	sleep(1);
	
	j1->colisiono(*j2);
	
	(this->mundo->get_mapa_activo()).mover(*j2,Direccion::Este, 0.5);
	std::cout << "- El jugador 2 tiene " << j2->get_puntos() << " puntos y esta en ";
	std::cout << j2->get_posicion() <<"\n";
	sleep(1);
	
	j2->colisiono(*j1);
	
}
