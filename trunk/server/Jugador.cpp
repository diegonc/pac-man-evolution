#include "Jugador.h"

Jugador::Jugador(int id, Tipo_Personaje personaje){
	this->id = id;
	this->set_personaje(personaje);
	this->dir = &(Direccion::Oeste); /* Arrancan para el oeste. */
	this->puntos = 0;
}
Jugador::Jugador(int id){
	this->id = id;
	this->dir = &(Direccion::Oeste); /* Arrancan para el oeste. */
	this->puntos = 0;
}

Tipo_Personaje Jugador::get_personaje(){
	return this->personaje;
}
void Jugador::set_personaje(Tipo_Personaje personaje){
	this->personaje = personaje;
}
void Jugador::set_posicion(Posicion &pos_nueva){
	this->posicion = pos_nueva;
}
Posicion& Jugador::get_posicion(){
	return this->posicion;
}
Direccion& Jugador::get_direccion() { 
	return *dir; 
}
int Jugador::get_id(){
	return this->id;
}
void Jugador::comer(Comestible& comestible){
	this->personaje->comer(comestible);
}
void Jugador::incrementar_puntos(int cant){
	this->puntos+= cant;
}
int Jugador::get_puntos(){
	return this->puntos;
}
void Jugador::colisiono(Jugador &jugador){
	this->personaje->colision(jugador);
}
