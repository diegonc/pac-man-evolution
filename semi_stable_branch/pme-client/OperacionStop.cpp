#include "OperacionStop.h"

#include <server/PaqueteStopCommon.h>
#include <sstream>
#include "BufferMensajes.h"


OperacionStop::OperacionStop( char Razon, int Puntuacion ){
	this->Razon = Razon;
	this->Puntuacion=Puntuacion;
}

void OperacionStop::ejecutar(ModeloCommon &modelo) {
	
	std::list<Jugador*> jugadores=modelo.get_jugadores();
	bool Encontrado=false;
	for (std::list<Jugador*>::iterator it=jugadores.begin();(it!=jugadores.end() && (!Encontrado));++it){
		Jugador* j=*it;
		if (j->get_personaje()->get_tipo()==Personaje::pacman){
			j->set_puntos(Puntuacion);
			Encontrado=true;
		}
	}


	int IDJUG;
	int PuntajMaximo=-100;
	for (std::list<Jugador*>::iterator it=jugadores.begin();(it!=jugadores.end() && (!Encontrado));++it){
		Jugador* j=*it;
		if (j->get_puntos()>PuntajMaximo){
			PuntajMaximo=j->get_puntos();
			IDJUG=j->get_id();
		}
	}
	

	std::string RazonStr="";
	std::stringstream ss;
	switch (Razon){
		case RazonPacmanGano:
			RazonStr="El PacMan gano el nivel";
			break;
		case RazonPacmanComido:
			RazonStr="El PacMan ha sido comido";
			break;
		case RazonPacmanDesconecto:
			RazonStr="El PacMan se desconecto";
			break;
		case RazonCantidadInsuficiente:
			RazonStr="Cantidad de jugadores Insuficiente";
			break;
		case RazonTerminoJuego:
			ss << "Se termino el juego, gano con ";
			ss << PuntajMaximo;
			ss << "el jugador ";
			ss << IDJUG;
			ss >> RazonStr;
			break;
		default:
			RazonStr="";			
	}

	if (RazonStr!="")
		BufferMensajes::get_instancia()->add_mensaje_critico(RazonStr);
	
}
