#include "MapImpMatriz.h"

MapaImpMatriz::MapaImpMatriz(Tipo_Dimensiones ancho, Tipo_Dimensiones alto){
	//TODO : VALIDAR ESTO!!!!!!
	this->ancho = ancho;
	this->alto = alto;
	
	matriz = new Casillero[alto][ancho];
}

MapaImpMatriz::~MapaImpMatriz(){
	delete this->matriz;
}

void MapaImpMatriz::mover( S_ptr<Jugador> jugador, Direccion dir ){
	
}

virtual void establecer_posicion_inicial(Jugador * jugador){
	
	
}

void MapaImpMatriz::agregar_comestible( Tipo_Comestible comestible, Posicion &posicion){
	
}

S_ptr<Comestible> MapaImpMatriz::get_comestible(Posicion &posicion){
	int coordenada_x = (int) posicion.get_x();
	int coordenada_y = (int) posicion.get_y();
	
	return (matriz[coordenada_y][coordenada_x]).comestible
}
	
Tipo_Dimensiones MapaImpMatriz::get_ancho(){
	return this->ancho;
}
	
Tipo_Dimensiones MapaImpMatriz::get_alto(){
	return this->alto;
}
