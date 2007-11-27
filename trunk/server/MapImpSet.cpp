#include "MapImpSet.h"

#include <iostream>

MapaImpSet::MapaImpSet(const Tipo_Dimensiones ancho, const Tipo_Dimensiones alto){
	//TODO : VALIDAR ESTO!!!!!!
	this->ancho = ancho;
	this->alto = alto;
}

MapaImpSet::~MapaImpSet(){
	std::set<Elemento,ComparadorElementoPosicion>::iterator it;
	
	S_ptr<Estructural> estruct_nulo;
	S_ptr<Estructural> estruct_aux;
	
	for(it = this->estructurales.begin(); it != this->estructurales.end(); it++){
		estruct_aux = (it->estructural);
		estruct_aux->set_arriba(estruct_nulo);
		estruct_aux->set_abajo(estruct_nulo);
		estruct_aux->set_derecha(estruct_nulo);
		estruct_aux->set_izquierda(estruct_nulo);
	
		
	}
	this->estructurales.clear();
}

void MapaImpSet::mover( Jugador& jugador, Direccion &dir, Tipo_Coordenada distancia ){
	
	Posicion posicion_jugador = jugador.get_posicion();
	S_ptr<Estructural> donde_estaba = this->get_estructural(posicion_jugador);
	//si esta en algun lugar del mapa
	if(! donde_estaba.es_nulo() ){
		posicion_jugador.incrementar(distancia,dir);		
		//Aca discretizo los cuadrantes.
		//Si cayo en el mismo estructural. Les pongo 1 unidad de separacion
		ComparadorPosicion comp;
		if(! comp(posicion_jugador, jugador.get_posicion()) ){
			//si cayeron distinto, me fijo si podia moverse para ese lado
			S_ptr<Estructural> vecino = donde_estaba->get_vecino(dir);
			if( !vecino.es_nulo() ){
				vecino->ingresar(jugador);
				jugador.set_posicion(posicion_jugador);
			}
			   
			//TODO.....VER QUE SE HACE SI NO SE PODIA MOVER PARA ESE LADO
		}
		else
			jugador.set_posicion(posicion_jugador);
	}			
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
	
	if( busqueda != estructurales.end() )
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
