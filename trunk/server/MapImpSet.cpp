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

void mover( Jugador * jugador, Direccion &dir ){
	
}

void MapaImpMatriz::establecer_posicion_inicial(Jugador * jugador){
	
	
}
void agregar_estructural(S_ptr<Estructural> e, Posicion &p){
									
	Elemento estructural_nuevo;
	estructural_nuevo.posicion = p;
	estructural_nuevo.estructural = e;
	estructurales.insert(estructural_nuevo);
			
}
S_ptr<Estructural> get_estructural(Posicion &p){
	std::set<Elemento, ComparadorPosicion>::iterator busqueda;
	
	Elemento estructural_busqueda;
	estructural_nuevo.posicion = p;
	
	busqueda = this->estructurales.find(estructural_busqueda);
	
	if(busqueda != estructurales::end)
		return busqueda->estructural;
	else
		return (S_ptr<Estructural> nulo);
}

Tipo_Dimensiones MapaImpMatriz::get_ancho(){
	return this->ancho;
}
	
Tipo_Dimensiones MapaImpMatriz::get_alto(){
	return this->alto;
}
