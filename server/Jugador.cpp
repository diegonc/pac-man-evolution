#include "Jugador.h"

Jugador::Jugador(int id, Tipo_Personaje personaje){
	this->id = id;
	this->set_personaje(personaje);
	this->dir = &(Direccion::Norte); /* Arrancan para el norte. */
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
void Jugador::ejecutar_operacion(Operacion& operacion){
	
}
void Jugador::comer(Comestible& comestible){
	this->personaje->comer(*this, comestible);
}
void Jugador::incrementar_puntos(int cant){
	this->puntos+= cant;
}
int Jugador::get_puntos(){
	return this->puntos;
}
