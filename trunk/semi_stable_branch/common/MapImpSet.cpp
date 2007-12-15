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
	std::map<unsigned int,Tipo_Estructural>::iterator it;
	Tipo_Estructural estruct_nulo;
	Tipo_Estructural estruct_aux;

	for(it = this->estructurales.begin(); it != this->estructurales.end(); it++){
		estruct_aux = it->second;
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
			//Si no estoy en el mismo estructural
			if(! comp(posicion_jugador,jugador.get_posicion()) ){
				//guardo la comida, ya que si la come la tengo que eliminar despues
				S_ptr<Comestible> com = vecino->get_comida();
				//obtengo los puntos antes de ingresar
				int puntosJugador = jugador.get_puntos();
				vecino->ingresar(jugador);
				//si variaron los puntos, quito el comestible de la lista ya que
				//lo comio
				if(jugador.get_puntos() != puntosJugador){
					this->quitar_comestible(com);
					this->set_cambio();
					NovedadComestible NovComestible(com,false);
					//this->avisar_observadores(&NovComestible);
				}
				
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
		/*if (p.get_x() < 0)
			p.set_x(p.get_x() + this->ancho);
		else
			if (p.get_x() >= this->ancho)
				p.set_x(p.get_x() - this->ancho);
		if (p.get_y() < 0)
			p.set_y(p.get_y() + this->alto);
		else
			if (p.get_y() >= this->alto)
				p.set_y(p.get_y() - this->alto);*/
		e_critico = get_estructural(p);
		if( e_critico.es_nulo() ){
			toca = true;
		}
		else{
			if(!donde_esta->tiene_conexion(e_critico)){
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
	unsigned int key = make_key(e->get_posicion() );

	estructurales[key] = e;
	S_ptr<Comestible> c = e->get_comida();
	if(! c.es_nulo() )
		comestibles[key] = c;
}
Tipo_Estructural MapaImpSet::get_estructural(Posicion &p){

	Tipo_Estructural e_retorno;
	unsigned int key = make_key(p);
	std::map<unsigned int, Tipo_Estructural>::iterator busqueda = estructurales.find(key);
	if( busqueda != estructurales.end() )
		e_retorno = estructurales[key];

	return e_retorno;
		
}

Tipo_Dimensiones MapaImpSet::get_ancho(){
	return this->ancho;
}

Tipo_Dimensiones MapaImpSet::get_alto(){
	return this->alto;
}
std::list<Tipo_Estructural > MapaImpSet::get_estructurales(){
	std::map<unsigned int, Tipo_Estructural>::iterator it;
	std::list<Tipo_Estructural> lista;

	it = this->estructurales.begin(); 
	while(it != this->estructurales.end()){
		lista.push_back((*it).second);
		it++;
	}
	return lista;
}

std::list<Tipo_Comestible > MapaImpSet::get_comestibles(){
	std::map<unsigned int, Tipo_Comestible>::iterator it;
	std::list<Tipo_Comestible> lista;

	it = this->comestibles.begin(); 
	while(it != this->comestibles.end()){
		lista.push_back((*it).second);
		it++;
	}
	return lista;
}

void MapaImpSet::quitar_comestible(Tipo_Comestible comestible){
	
	if( !comestible.es_nulo() ){
		std::map<unsigned int, Tipo_Comestible>::iterator it;
		unsigned int key = make_key(comestible->get_posicion());
		it = comestibles.find(key);		
		if(it != comestibles.end() )
			comestibles.erase(key);		

		if(this->comestibles.size() == 0){
			this->set_cambio();
			this->avisar_observadores(NULL);
		}
	}
}

void MapaImpSet::refresh(unsigned int vertice){
	std::map<unsigned int, Tipo_Comestible>::iterator it;
	
	it = comestibles.find(vertice);		
	std::cout << "Busca el comestible en : " << vertice << "\n";
	if(it != comestibles.end() ){
		std::cout << "La borro porque la encontro ;)\n";
		comestibles.erase(vertice);		
	}
	else
		std::cout << "No la encontro =(\n";
}
void MapaImpSet::refresh(unsigned int vertice, Comestible::Enum_Comestible tipo_comestible){
	ComestibleFactory fab;
	
	Posicion posicion = unmake_key(vertice);	
	posicion.set_x(posicion.get_x() + 0.5);
	posicion.set_y(posicion.get_y() + 0.5);
	
	Comestible * c = fab.construir(tipo_comestible, posicion);
	
	S_ptr<Comestible> comestible_nuevo(c);
	
	comestibles[vertice] = comestible_nuevo;
}

unsigned int MapaImpSet::make_key(Posicion &p){
	unsigned int fila = (unsigned int) floor(p.get_y());
	unsigned int col =  (unsigned int) floor(p.get_x());
	return ( (fila * this->get_ancho()) + col);
}
Posicion MapaImpSet::unmake_key(unsigned int key){
        int Col=key % this->get_ancho();
        int Fila=(int) floor(key / this->get_ancho());
	Posicion P(Col,Fila);
	return P;
}
