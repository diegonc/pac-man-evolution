#include "MapImpSet.h"

#include <math.h>
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
	Tipo_Estructural estruct_aux;	
	
	for(it = this->estructurales.begin(); it != this->estructurales.end(); it++){
		estruct_aux = *it;
		estruct_aux->set_arriba(estruct_nulo);
		estruct_aux->set_abajo(estruct_nulo);
		estruct_aux->set_derecha(estruct_nulo);
		estruct_aux->set_izquierda(estruct_nulo);
	}
	this->estructurales.clear();
}

void MapaImpSet::mover( Jugador& jugador, Tipo_Coordenada distancia ){
	Posicion posicion_jugador = jugador.get_posicion();
	S_ptr<Estructural> donde_estaba = this->get_estructural(posicion_jugador);
	//si esta en algun lugar del mapa
	if(! donde_estaba.es_nulo() ){
		posicion_jugador.incrementar(distancia,jugador.get_direccion());
		
		//si cayeron distinto, me fijo si podia moverse para ese lado
		S_ptr<Estructural> vecino = donde_estaba->get_vecino(jugador.get_direccion());
		
		Tipo_Coordenada dim_actual;
		Tipo_Coordenada dim_final;
		set_dim(posicion_jugador, dim_actual, dim_final, jugador.get_direccion() );
		if( tocando( dim_actual, dim_final, vecino, jugador) ){
			//Aca discretizo los cuadrantes.
			//Si cayo en el mismo estructural. 
			ComparadorPosicion comp;
			if(! comp(posicion_jugador, jugador.get_posicion()) ){
				
				if( !vecino.es_nulo() ){
					S_ptr<Comestible> com = vecino->get_comida();
					vecino->ingresar(jugador);
					if(vecino->get_comida().es_nulo() ){
						this->quitar_comestible(com);
					}
					jugador.set_posicion(posicion_jugador);
				}
				//TODO.....VER QUE SE HACE SI NO SE PODIA MOVER PARA ESE LADO
			}
			else
				jugador.set_posicion(posicion_jugador);
			
		}	
	}
}
bool MapaImpSet::tocando(Tipo_Coordenada &dim_actual, Tipo_Coordenada &dim_final, S_ptr<Estructural> vecino, Jugador& jugador){
	
	if(vecino.es_nulo() ){
		Tipo_Coordenada result = dim_final - dim_actual;
		
		if(result < 0)
			result = -1 * result;
		
		if (result<= jugador.get_personaje()->get_radio() ){
			return true;
		}else{
			return false;	
		}
	}
	else
		return true;
}
void MapaImpSet::set_dim(Posicion& p, Tipo_Coordenada& dim_actual, Tipo_Coordenada& dim_final, Direccion& dir){
	
	switch(dir.get_dir()){
		case NORTE:
				dim_final = floor(p.get_y());
				dim_actual = p.get_y();
				break;
		case SUR:
				dim_final = ceil(p.get_y());
				dim_actual = p.get_y();
				break;
		case ESTE:
				dim_final = ceil(p.get_x());
				dim_actual = p.get_x();
				break;
		case OESTE:
				dim_final = floor(p.get_x());
				dim_actual = p.get_x();
				break;		
	}		
}
void MapaImpSet::agregar_estructural(S_ptr<Estructural> e){
	
	estructurales.insert(e);
	S_ptr<Comestible> c = e->get_comida();
	if(! c.es_nulo() )
		this->comestibles.push_back(c);
	
}
S_ptr<Estructural> MapaImpSet::get_estructural(Posicion &p){

	std::set<Tipo_Estructural, CompSptrEstructuralPosicion>::iterator busqueda;
	busqueda = estructurales.begin();
	
	bool encontrado = false;
	ComparadorPosicion comp;
	Tipo_Estructural aux;
	
	while( !encontrado && busqueda != estructurales.end() ){
		aux = *busqueda;
		if( comp(aux->get_posicion(), p) )
			encontrado = true;
		else
			busqueda++;
	}
	if( encontrado)
		return aux;
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
	std::set<Tipo_Estructural>::iterator it;
	std::list<Tipo_Estructural> lista;
	
	for(it = this->estructurales.begin(); it != this->estructurales.end(); it++)
		lista.push_back(*it);
	return lista;
}

std::list<S_ptr<Comestible> > MapaImpSet::get_comestibles(){
	return this->comestibles;
}

void MapaImpSet::quitar_comestible(S_ptr<Comestible> comestible){
	std::list<S_ptr<Comestible> >::iterator it = this->comestibles.begin();
	bool encontrado = false;
	
	while( !encontrado && it != this->comestibles.end() ){
		if( comestible == *it ){
			comestibles.erase(it);
			encontrado = true;
		}
		else
			it++;
	}
}
