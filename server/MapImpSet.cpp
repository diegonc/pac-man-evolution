#include "MapImpSet.h"

#include <iostream>

MapaImpSet::MapaImpSet(const Tipo_Dimensiones ancho, const Tipo_Dimensiones alto){
	//TODO : VALIDAR ESTO!!!!!!
	this->ancho = ancho;
	this->alto = alto;
}

MapaImpSet::~MapaImpSet(){
	this->comestibles.clear();
	
	std::set<Tipo_Estructural,CompSptrEstructuralPosicion>::iterator it;
	Tipo_Estructural estruct_nulo;
	
	for(it = this->estructurales.begin(); it != this->estructurales.end(); it++){
		it->set_arriba(estruct_nulo);
		it->set_abajo(estruct_nulo);
		it->set_derecha(estruct_nulo);
		it->set_izquierda(estruct_nulo);
	}
	this->estructurales.clear();
}

void MapaImpSet::mover( Jugador& jugador, Tipo_Coordenada distancia ){
	
	Posicion posicion_jugador = jugador.get_posicion();
	S_ptr<Estructural> donde_estaba = this->get_estructural(posicion_jugador);
	//si esta en algun lugar del mapa
	if(! donde_estaba.es_nulo() ){
		posicion_jugador.incrementar(distancia,jugador.get_direccion());		
		//Aca discretizo los cuadrantes.
		//Si cayo en el mismo estructural. Les pongo 1 unidad de separacion
		ComparadorPosicion comp;
		if(! comp(posicion_jugador, jugador.get_posicion()) ){
			//si cayeron distinto, me fijo si podia moverse para ese lado
			S_ptr<Estructural> vecino = donde_estaba->get_vecino(jugador.get_direccion());
			if( !vecino.es_nulo() ){
				S_ptr<Comestible> com = vecino->get_comestible();
				vecino->ingresar(jugador);
				if(! vecino->get_comestible.es_nulo() )
					this->quitar_comestible(com);
				jugador.set_posicion(posicion_jugador);
			}
			//TODO.....VER QUE SE HACE SI NO SE PODIA MOVER PARA ESE LADO
		}
		else
			jugador.set_posicion(posicion_jugador);
	}			
}
void MapaImpSet::agregar_estructural(S_ptr<Estructural> e){
		
	estructurales.insert(e);
	S_ptr<Comestible> c = e->get_comestible();
	if(! c.es_nulo() )
		this->comestibles.push_back(c);
	
}
S_ptr<Estructural> MapaImpSet::get_estructural(Posicion &p){

	std::set<Tipo_Estructural, CompSptrEstructuralPosicion>::iterator busqueda;
	
	busqueda = estructurales.begin();
	
	bool encontrado = false;
	
	ComparadorPosicion comp;
	
	while( !encontrado && busqueda != estructurales.end() ){
		if( comp(*busqueda->get_posicion(), p) )
			encontrado = true;
		else
			busqueda++;
	}
		
	if( encontrado)
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
std::list<S_ptr<Estructural> > MapaImpSet::get_estructurales(){
	std::set<Elemento>::iterator it;
	std::list<S_ptr<Estructural> > lista;
	
	for(it = this->estructurales.begin(); it != this->estructurales.end(); it++)
		lista.push_back(it->estructural);
	return lista;
}

std::list<S_ptr<Objeto> > MapaImpSet::get_comestibles(){
	return this->comestibles;
}

void MapaImpSet::quitar_comestible(S_ptr<Comestible> comestible){
	std::list<S_ptr<Comestible> >::iterator it = this->comestibles.begin();
	bool encontrado = false;
	
	while( != encontrado && it != this->comestibles.end() ){
		if( comestible == *it ){
			comestibles.erase(it);
			encontrado = true;
		}
		else
			it++;
	}
}
