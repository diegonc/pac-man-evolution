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

void agregar_casillero( S_ptr<Casillero> casillero_nuevo, Posicion posicion, 
	                            bool tiene_vecino_izq, bool tiene_vecino_arr ){
									
	int coordenada_x = (int) posicion.get_x();
	int coordenada_y = (int) posicion.get_y();
	//agrego el casillero								
	matriz[coordenada_y][coordenada_x] = casillero_nuevo;
	//si tiene vecino los vinculo
	if(tiene_vecino_izq){
		casillero_nuevo->set_izquierda(matriz[coordenada_y][coordenada_x-1] );
		matriz[coordenada_y][coordenada_x-1]->set_derecha(casillero_nuevo);
	}
	if(tiene_vecino_arr){
		casillero_nuevo->set_arriba(matriz[coordenada_y-1][coordenada_x]);
		matriz[coordenada_y-1][coordenada_x]->set_abajo(casillero_nuevo);		
	}
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
