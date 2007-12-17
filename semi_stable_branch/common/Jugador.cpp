#include "Jugador.h"

#if 0
Jugador::Jugador(unsigned int id, Tipo_Personaje personaje){
	this->id = id;
	this->set_personaje(personaje);
	this->dir = new Direccion(Direccion::Este); /* Arrancan para el este. */
	this->puntos = 0;
}
#endif

Jugador::Jugador(unsigned int id){
	this->id = id;
	this->personaje = NULL;
	this->dir = new Direccion(Direccion::Este); /* Arrancan para el este. */
	this->puntos = 0;
	this->invalido = false;
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
unsigned int Jugador::get_id(){
	return this->id;
}
bool Jugador::comer(Comestible& comestible){
	return this->personaje->comer(comestible);
}
void Jugador::incrementar_puntos(int cant){
	this->puntos+= cant;
}
int Jugador::get_puntos(){
	return this->puntos;
}
void Jugador::colisiono(Jugador * jugador){
	this->personaje->colision(jugador);
}
void Jugador::set_direccion(Direccion  *dir){
	this->dir = dir;
}
Jugador::~Jugador(){
   delete this->dir;
	delete this->personaje;
   this->personaje = NULL;
}
void Jugador::set_puntos(int puntos){
	this->puntos = puntos;
}
void Jugador::quitar_personaje(){
   if(this->personaje != NULL)   
   	delete this->personaje;	
}

void Jugador::set_invalido(){
	this->invalido = false;
}
bool Jugador::es_invalido(){
	return this->invalido;
}

