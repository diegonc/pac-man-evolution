#include "PacMan.h"
#include <math.h>

#define RADIO_PACMAN	0.5

PacMan::PacMan(Jugador *jugador):Personaje(jugador,RADIO_PACMAN){
	this->set_power_up(false);
}

void PacMan::comer(Comestible& comestible){
	(this->get_jugador()).incrementar_puntos(comestible.get_puntos());
	comestible.afectar_personaje(*this);
}
void PacMan::colision(Jugador& jugador){
	
	if(jugador.get_id() != get_jugador().get_id() ){
		Tipo_Coordenada distancia;
		
		distancia = pow( get_jugador().get_posicion().get_x() - 	
						 jugador.get_posicion().get_x() , 2);
		
		distancia += pow( get_jugador().get_posicion().get_y() - 	
						  jugador.get_posicion().get_y() , 2);
		
		distancia = sqrt(distancia);
		if(distancia  <= (this->get_radio() + jugador.get_personaje()->get_radio() ) ){
			if( this->tiene_power_up() ){
				jugador.get_personaje()->matar();
			}
			else{
				this->matar();			
			}
		}
		
	}	
}
void PacMan::set_power_up(bool activado){
	this->power_up_activado = activado;
}
bool PacMan::tiene_power_up(){
	return this->power_up_activado;
}
Personaje::Enum_Personaje PacMan::get_tipo(){
	return pacman;
}
