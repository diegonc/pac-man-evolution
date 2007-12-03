#include "MapImpSet.h"

#include <math.h>
#include <iostream>

#define INCREMENTO_PHI 	0.5
#define DOS_PI			6.28

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
	S_ptr<EstructuralUnitario> donde_estaba = this->get_estructural(posicion_jugador);
	//si esta en algun lugar del mapa
	if(! donde_estaba.es_nulo() ){


		//si cayeron distinto, me fijo si podia moverse para ese lado
		S_ptr<EstructuralUnitario> vecino = donde_estaba->get_vecino(jugador.get_direccion());

		/*Tipo_Coordenada dim_actual;
		Tipo_Coordenada dim_final;
		//paso a una dimension el problema
		set_dim(posicion_jugador, dim_actual, dim_final, jugador.get_direccion() );
		//si no esta tocando alguno que es pared
		if( !tocando( dim_actual, dim_final, vecino, jugador) ){*/
		posicion_jugador.incrementar(distancia,jugador.get_direccion());
		if( !tocando( jugador, posicion_jugador) ){
			ComparadorPosicion comp;
			if(! comp(posicion_jugador, jugador.get_posicion()) ){
				S_ptr<Comestible> com = vecino->get_comida();
				int puntosJugador = jugador.get_puntos();
				vecino->ingresar(jugador);
				if(jugador.get_puntos() != puntosJugador){
				//if(vecino->get_comida().es_nulo()){
					this->quitar_comestible(com);
				}
				//jugador.set_posicion(posicion_jugador);
				
				//TODO.....VER QUE SE HACE SI NO SE PODIA MOVER PARA ESE LADO
			}
			//else
				jugador.set_posicion(posicion_jugador);
		}

	}
	
}

bool MapaImpSet::tocando(Jugador &jugador, Posicion &pnueva){
	S_ptr<EstructuralUnitario> e_critico;
		
	Tipo_Coordenada x0 = pnueva.get_x();
	Tipo_Coordenada y0 = pnueva.get_y();
	double phi = 0.0;
	double radio = jugador.get_personaje()->get_radio();
	bool toca = false;
	while( phi < DOS_PI && !toca/*2Pi*/ ){
		Posicion p(	radio * cos(phi) + x0, radio * sin(phi) + y0 );
		e_critico = get_estructural(p);
		if( e_critico.es_nulo() ){
			toca = true;
		}
		else
			phi += INCREMENTO_PHI;
	}
	return toca;
}
/*
bool MapaImpSet::tocando(Tipo_Coordenada dim_actual, Tipo_Coordenada dim_final, S_ptr<EstructuralUnitario> vecino, Jugador& jugador){
	
	Tipo_Coordenada result = dim_final - dim_actual;
	Tipo_Coordenada mod_result;
	double radio = jugador.get_personaje()->get_radio();
	
	if(mod_result < 0)
		mod_result = -1 * mod_result;
	
	
	if ( (mod_result < radio ) && vecino.es_nulo() )
		//aca entra si a donde se mueve es nulo y si la distancia entre los casilleros
		//y el centro del pacman es menor que el radio (por lo tanto choca)
		return true;
	else{
		return false;
	}
		
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
}*/
void MapaImpSet::agregar_estructural(S_ptr<EstructuralUnitario> e){
	S_ptr<EstructuralUnitario> e_aux = this->get_estructural(e->get_posicion());
	//if( !e_aux.es_nulo() )
		//quitar_comestible(e_aux->get_comida() );
	
	estructurales.insert(e);
	S_ptr<Comestible> c = e->get_comida();
	if(! c.es_nulo() )
		this->comestibles.push_back(c);
	
	
	
}
S_ptr<EstructuralUnitario> MapaImpSet::get_estructural(Posicion &p){

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
		S_ptr<EstructuralUnitario> nulo;
		return nulo;
	}
}

Tipo_Dimensiones MapaImpSet::get_ancho(){
	return this->ancho;
}

Tipo_Dimensiones MapaImpSet::get_alto(){
	return this->alto;
}
std::list<S_ptr<EstructuralUnitario> > MapaImpSet::get_estructurales(){
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
	
	if( !comestible.es_nulo() ){
		std::list<S_ptr<Comestible> >::iterator it = this->comestibles.begin();
		bool encontrado = false;
		S_ptr<Comestible> aux;
		
		while( !encontrado && it != this->comestibles.end() ){
			aux = *it;
			//std::cout << &(*comestible)  << " ---- " << &(*aux)  << "\n";
			///if( comestible == *it ){
			if( &(*comestible) == &(*aux) ){
				comestibles.erase(it);
				encontrado = true;
			}
			else
				it++;
		}
		if(this->comestibles.size() == 0){
			this->set_cambio();
			this->avisar_observadores(NULL);
		}
	}
}
