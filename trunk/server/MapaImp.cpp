#include "MapaImp.h"
#include <list>

MapaImp::MapaImp(Tipo_Dimensiones ancho, Tipo_Dimensiones alto){
	//TODO revisar esto como para que no bardeen

	this->ancho = ancho;
	this->alto = alto;	
}

MapaImp::~MapaImp()
{

}

void MapaImp::mover( S_ptr<Jugador> jugador, Direccion dir )
{

}
virtual S_ptr<Comestible> get_comestible(Tipo_Coordenada pos_x, Tipo_Coordenada pos_y){
	
}
/*S_ptr<Jugador> MapaImp::get_jugador( int id )
{
	
}

S_ptr<Jugador> MapaImp::get_jugador(Tipo_Coordenada pos_x, Tipo_Coordenada pos_y){

}*/
MapaImp::Tipo_Dimensiones get_ancho(){
	return this->ancho;
}
Tipo_Dimensiones get_alto(){
	return this->alto;
}
