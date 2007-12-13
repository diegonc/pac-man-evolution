#include "MapImpSet.h"

#include <math.h>
#include "../common/EstructuralPasillo.h"

#include <iostream>

//definiciones para usar
#define INCREMENTO_PHI 	0.5
#define DOS_PI			6.28

MapaImpSet::MapaImpSet(const Tipo_Dimensiones ancho, const Tipo_Dimensiones alto){
	//TODO : VALIDAR ESTO!!!!!!
	this->ancho = ancho;
	this->alto = alto;
}
MapaImpSet::~MapaImpSet(){
	//limpia los comestibles
	this->comestibles.clear();
	
	//recorro los estructurales y los desconecto para que no quede memoria
	//colgada
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
		//obtengo a donde se tiene que mover
		S_ptr<EstructuralUnitario> vecino = donde_estaba->get_vecino(jugador.get_direccion());
		//incremento la distancia
		posicion_jugador.incrementar(distancia,jugador.get_direccion());
		//si no esta tocando alguna pared o esquina prohibida
		if( !tocando( jugador,donde_estaba, posicion_jugador) ){
			ComparadorPosicion comp;
			//si cayeron distinto, me fijo si podia moverse para ese lado
			if(! comp(posicion_jugador,jugador.get_posicion()) ){
				//guardo la comida, ya que si la come la tengo que eliminar despues
				S_ptr<Comestible> com = vecino->get_comida();
				//obtengo los puntos antes de ingresar
				int puntosJugador = jugador.get_puntos();
				vecino->ingresar(jugador);
				//si variaron los puntos, quito el comestible de la lista ya que
				//lo comio
				if(jugador.get_puntos() != puntosJugador)
					this->quitar_comestible(com);
				
			}
			//si se movio correctamente, le modifico la posicion al jugador
			jugador.set_posicion(posicion_jugador);
		}

	}
	
}
bool MapaImpSet::tocando(Jugador &jugador, S_ptr<EstructuralUnitario> donde_esta, Posicion &pnueva){
	S_ptr<EstructuralUnitario> e_critico;
		
	Tipo_Coordenada x0 = pnueva.get_x();
	Tipo_Coordenada y0 = pnueva.get_y();
	double phi = 0.0;
	double radio = jugador.get_personaje()->get_radio();
	bool toca = false;
	//lo que hace basicamente es recorrer todos los puntos del radio del pacman
	//y ver si tocan un lugar que no puede, digase pared, esquina.
	//Se puede modificar el paso como para que no recorra todos los puntos
	while( phi < DOS_PI && !toca/*2Pi*/ ){
		Posicion p(	(radio-0.1) * cos(phi) + x0, (radio-0.1) * sin(phi) + y0 );
		e_critico = get_estructural(p);
		if( e_critico.es_nulo() ){
			toca = true;
		}
		else{
			if(!donde_esta->tiene_conexion(e_critico) ){
				toca = true;
				//std::cout << "Toca uno critico donde no tiene conexion\n";	
			}
			else
				phi += INCREMENTO_PHI;
		}
	}
	return toca;
}

void MapaImpSet::agregar_estructural(S_ptr<EstructuralUnitario> e){
	S_ptr<EstructuralUnitario> e_aux = this->get_estructural(e->get_posicion());
		
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
			
			if( comestible == *it ){
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

void MapaImpSet::refresh( std::list< S_ptr<Comestible> >& comestibles_totales ){
	
	
	//limpia los comestibles
	this->comestibles.clear();
	//CREO QUE NO TIENE SENTIDO HACERLO
	/*
	//recorro los estructurales y les saco el comestible
	std::set<Tipo_Estructural,CompSptrEstructuralPosicion>::iterator it;
	S_ptr<Comestible> comestible_nulo;*/
	Tipo_Estructural e_aux;
	/*EstructuralPasillo *pasillo;
	it = this->estructurales.begin();
	while( it != this->estructurales.end() ){
		e_aux = *it;
		pasillo = dynamic_cast<EstructuralPasillo *>(&(*e_aux));		
		if(pasillo != NULL)
			pasillo->set_comida(comestible_nulo);
		++it;
		
	}*/
	
	std::list< S_ptr<Comestible> >::iterator it_comestibles;
	std::cout << comestibles_totales.size() << "\n";
	it_comestibles = comestibles_totales.begin();
	S_ptr<Comestible> c_aux; 
	while(it_comestibles != comestibles_totales.end() ){
		/e_aux = get_estructural((*it_comestibles)->get_posicion());
		if(! e_aux.es_nulo() ){
			pasillo = dynamic_cast<EstructuralPasillo *>(&(*e_aux));		
			if(pasillo != NULL){
				c_aux = *it_comestibles;
				//pasillo->set_comida(c_aux);	
				
				//std::cout << c_aux->get_posicion() << "\n";
				c_aux->get_posicion().set_x(e_aux->get_posicion().get_x() + 0.5);
				c_aux->get_posicion().set_y(e_aux->get_posicion().get_y() + 0.5);
				//std::cout << c_aux->get_posicion() << "\n";
				//SETTEAR LA POSICION DEL COMESTIBLE
				comestibles.push_back(c_aux);
			}			
		}
		++it_comestibles;
		
	}
	std::cout << "<~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~>\n";
	//std::cout << "Recarge " << comestibles_totales.size() << " comestibles\n";
}
