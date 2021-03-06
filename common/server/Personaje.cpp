#include <server/Personaje.h>
#include <iostream>
const char Personaje::pacman = 'p';
const char Personaje::fantasma = 'f';

Personaje::Personaje(Jugador * jugador, double radio){
	this->radio = radio;
	this->jugador = jugador;
	vivo = true;
}
	
Jugador* Personaje::get_jugador(){
	return this->jugador;
}
	
void Personaje::matar(){
	this->vivo = false;
}
void Personaje::revivir(){
	this->vivo = true;
}		
bool Personaje::esta_vivo(){
	return this->vivo;
}
Personaje::~Personaje(){}

double Personaje::get_radio(){return this->radio;}

void Personaje::set_jugador(Jugador * jugador){
	this->jugador = jugador;
}
