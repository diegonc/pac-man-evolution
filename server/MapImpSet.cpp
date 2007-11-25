#include "MapImpSet.h"

MapaImpSet::MapaImpSet(const Tipo_Dimensiones ancho, const Tipo_Dimensiones alto){
	//TODO : VALIDAR ESTO!!!!!!
	this->ancho = ancho;
	this->alto = alto;
}

MapaImpSet::~MapaImpSet(){}

void MapaImpSet::mover( Jugador * jugador, Direccion &dir ){
	
}
void MapaImpSet::agregar_estructural(S_ptr<Estructural> e, Posicion &p){
									
	Elemento estructural_nuevo;
	estructural_nuevo.posicion = p;
	estructural_nuevo.estructural = e;
	estructurales.insert(estructural_nuevo);
			
}
S_ptr<Estructural> MapaImpSet::get_estructural(Posicion &p){
	std::set<Elemento, ComparadorPosicion>::iterator busqueda;
	
	Elemento estructural_busqueda;
	estructural_busqueda.posicion = p;
	
	busqueda = this->estructurales.find(estructural_busqueda);
	
	if(busqueda != estructurales.end())
		return busqueda->estructural;
	else{
		S_ptr<Estructural> nulo;
		return nulo;
	}
}

Tipo_Dimensiones MapaImpSet::get_ancho(){
	return this->ancho;
}
	
Tipo_Dimensiones MapaImpSet::get_alto(){
	return this->alto;
}
