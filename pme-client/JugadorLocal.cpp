#include "JugadorLocal.h"

S_ptr<JugadorLocal> JugadorLocal::instancia;

JugadorLocal::JugadorLocal(){
	set_id(-1); //asi no grafica nada hasta que no me lo settean
}	
JugadorLocal::JugadorLocal(JugadorLocal &j){}
		
S_ptr<JugadorLocal> JugadorLocal::get_instancia(){
	if( instancia.es_nulo())
		instancia = S_ptr<JugadorLocal>(new JugadorLocal());
	return instancia;
}
void JugadorLocal::set_id(unsigned int id_jugador){
	this->id = id_jugador;
	
}
unsigned int JugadorLocal::get_id(){
	return this->id;
}

void JugadorLocal::set_pacman( bool p )
{
	esPacman = p;
}

bool JugadorLocal::get_pacman()
{
	return esPacman;
}
