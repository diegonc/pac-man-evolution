#include "MapImpMatriz.h"

MapaImpMatriz::MapaImpMatriz(const Tipo_Dimensiones ancho, const Tipo_Dimensiones alto){
	//TODO : VALIDAR ESTO!!!!!!
	this->ancho = ancho;
	this->alto = alto;
	
	matriz = new S_ptr<Casillero>*[ancho];
	for (Tipo_Dimensiones indice = 0; indice < ancho; indice++)
		matriz[indice] = new S_ptr<Casillero>[alto];
}

MapaImpMatriz::~MapaImpMatriz(){
	for(Tipo_Dimensiones indice = 0; indice < ancho; indice++)
		delete[] matriz[indice];
	delete this->matriz;
}

void MapaImpMatriz::mover( Jugador * jugador, Direccion &dir ){
	
}

void MapaImpMatriz::establecer_posicion_inicial(Jugador * jugador){
	
	
}

void MapaImpMatriz::agregar_comestible( ComestibleFactory::Tipo_Comestible comestible, Posicion &posicion){
	
}

/*S_ptr<Comestible> MapaImpMatriz::get_comestible(Posicion &posicion){
	int coordenada_x = (int) posicion.get_x();
	int coordenada_y = (int) posicion.get_y();
	
	return (matriz[coordenada_y][coordenada_x]).comestible
}*/
	
Tipo_Dimensiones MapaImpMatriz::get_ancho(){
	return this->ancho;
}
	
Tipo_Dimensiones MapaImpMatriz::get_alto(){
	return this->alto;
}
