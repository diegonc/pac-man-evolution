#include "PacMan.h"

#define RADIO_PACMAN	0.5

void PacMan::comer(Jugador& jugador, Comestible& comestible){
	jugador.incrementar_puntos(comestible.get_puntos());
	comestible.afectar_personaje(*this);
}
void PacMan::colision(Jugador& jugador){

}
void PacMan::set_power_up(bool activado){
	this->power_up_activado = activado;
}
bool PacMan::tiene_power_up(){
	return this->power_up_activado;
}
