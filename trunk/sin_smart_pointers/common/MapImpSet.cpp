#include "MapImpSet.h"

#include <math.h>
#include "../common/EstructuralPasillo.h"

#include <iostream>

//definiciones para usar
#define INCREMENTO_PHI 	0.5
#define DOS_PI			6.28


MapaImpSet::MapaImpSet(const Tipo_Dimensiones ancho, const Tipo_Dimensiones alto){
	this->ancho = ancho;
	this->alto = alto;
}
MapaImpSet::~MapaImpSet(){

	std::map<unsigned int,EstructuralUnitario *>::iterator it;
	EstructuralUnitario * estruct_aux;
	
	it = this->estructurales.begin();
	while( it != this->estructurales.end() ){
		estruct_aux = it->second;
		delete estruct_aux;
		estruct_aux = NULL;
		it++;
	}
	this->estructurales.clear();
}
void MapaImpSet::mover( Jugador& jugador, Tipo_Coordenada distancia ){
	Posicion posicion_jugador = jugador.get_posicion();
	EstructuralUnitario * donde_estaba = this->get_estructural(posicion_jugador);
	//si esta en algun lugar del mapa
	if(donde_estaba != NULL){
		//incremento la distancia
		posicion_jugador.incrementar(distancia,jugador.get_direccion());
		//si no esta tocando alguna pared o esquina prohibida
		if( !tocando( jugador,donde_estaba, posicion_jugador) ){
			ComparadorPosicion comp;
			//Si no estoy en el mismo estructural
			if(! comp(posicion_jugador,jugador.get_posicion()) ){
				//obtengo a donde se tiene que mover
				EstructuralUnitario * vecino = donde_estaba->get_vecino(jugador.get_direccion());
				//guardo la comida, ya que si la come la tengo que eliminar despues
				Comestible * com = vecino->get_comida();
				//obtengo los puntos antes de ingresar
				int puntosJugador = jugador.get_puntos();
				vecino->ingresar(jugador);
				//si variaron los puntos, quito el comestible de la lista ya que
				//lo comio
				if(jugador.get_puntos() != puntosJugador){
					//this->quitar_comestible(com);
					this->set_cambio();
					NovedadComestible NovComestible(com,false);
					this->avisar_observadores(&NovComestible);
				}
				
			}
			//si se movio correctamente, le modifico la posicion al jugador
			corregir_posicion(posicion_jugador);			
			jugador.set_posicion(posicion_jugador);
		}

	}
	
}

bool MapaImpSet::tocando(Jugador &jugador, EstructuralUnitario * donde_esta, Posicion &pnueva){
	EstructuralUnitario * e_critico = NULL;
		
	Tipo_Coordenada x0 = pnueva.get_x();
	Tipo_Coordenada y0 = pnueva.get_y();
	double phi = 0.0;
	double radio = jugador.get_personaje()->get_radio();
	bool toca = false;
	//lo que hace basicamente es recorrer todos los puntos del radio del pacman
	//y ver si tocan un lugar que no puede, digase pared, esquina.
	//Se puede modificar el paso como para que no recorra todos los puntos
	while( phi < DOS_PI && !toca/*2Pi*/ ){
		Posicion p(	(radio-0.15) * cos(phi) + x0, (radio-0.15) * sin(phi) + y0 );
		
      	corregir_posicion(p);
		
		e_critico = get_estructural(p);

		if( e_critico == NULL){
			toca = true;
		}else{
			if(e_critico->get_tipo() != EstructuralUnitario::Casa_Fantasma){			
				if(!donde_esta->tiene_conexion(e_critico) ){
					toca = true;
				}
				else
					phi += INCREMENTO_PHI;
			}
			else
				phi += INCREMENTO_PHI;
	
		}
	}
	return toca;	
	
}

void MapaImpSet::agregar_estructural(EstructuralUnitario * e){
	unsigned int key = make_key(e->get_posicion() );
	estructurales.erase(key);
	estructurales[key] = e;
	std::cout << e->get_posicion() << "\n";
}
EstructuralUnitario * MapaImpSet::get_estructural(Posicion &p){
	EstructuralUnitario * e_retorno = NULL;
	unsigned int key = make_key(p);
	std::map<unsigned int, EstructuralUnitario *>::iterator busqueda = estructurales.find(key);
	if( busqueda != estructurales.end() )
		e_retorno = estructurales[key];

	return e_retorno;
}
std::list<EstructuralUnitario * > MapaImpSet::get_estructurales(){
	std::map<unsigned int, EstructuralUnitario *>::iterator it;
	std::list<EstructuralUnitario *> lista;

	it = this->estructurales.begin(); 
	while(it != this->estructurales.end()){
		lista.push_back((*it).second);
		it++;
	}
	return lista;
}
std::list<Comestible * > MapaImpSet::get_comestibles(){
	std::map<unsigned int, EstructuralUnitario *>::iterator it;
	std::list<Comestible *> lista;
	Comestible * comestible;
	
	it = this->estructurales.begin(); 
	while(it != this->estructurales.end()){
		comestible = ((*it).second)->get_comida();
		if(comestible != NULL){
			if(!comestible->es_invalido())
				lista.push_back(comestible);
		}
		it++;
	}
	return lista;
}
Tipo_Dimensiones MapaImpSet::get_ancho(){
	return this->ancho;
}

Tipo_Dimensiones MapaImpSet::get_alto(){
	return this->alto;
}
void MapaImpSet::refresh(unsigned int vertice){
	std::map<unsigned int, EstructuralUnitario * >::iterator it;
	
	it = estructurales.find(vertice);		
	if(it != estructurales.end() ){
		Comestible * c = ((*it).second)->get_comida();
		if( c != NULL )
			c->set_invalido();
	}
	
}
void MapaImpSet::refresh(unsigned int vertice, Comestible::Enum_Comestible tipo_comestible){
	ComestibleFactory fab;
	std::map<unsigned int, EstructuralUnitario *>::iterator it;
	
	Posicion posicion = unmake_key(vertice);	
	posicion.set_x(posicion.get_x() + 0.5);
	posicion.set_y(posicion.get_y() + 0.5);
	
	Comestible * c = fab.construir(tipo_comestible, posicion);
	
	it = estructurales.find(vertice);		
	if(it != estructurales.end() )
		((*it).second)->set_comida(c);
}
EstructuralUnitario * MapaImpSet::get_salida_pacman(){
	std::list< EstructuralUnitario * >::iterator it_estructurales;
	std::list< EstructuralUnitario * > estructurales;
	EstructuralUnitario * salida_pacman;
	bool encontro = false;
	
	estructurales = this->get_estructurales();
	it_estructurales = estructurales.begin();
	
	while( (it_estructurales != estructurales.end()) && (!encontro) ){
		if( (*it_estructurales)->get_tipo() == EstructuralUnitario::Salida_Pacman ){
			salida_pacman = *it_estructurales;
			encontro = true;
		}
		++it_estructurales;
	}
	return salida_pacman;
}
std::list<EstructuralUnitario *> MapaImpSet::get_casa_fantasma(){
	std::list< EstructuralUnitario * >::iterator it_estructurales;
	std::list< EstructuralUnitario * > estructurales;
	std::list< EstructuralUnitario * > casas_fantasma;
	
	estructurales = this->get_estructurales();
	it_estructurales = estructurales.begin();
	
	while(it_estructurales != estructurales.end() ){
		if( (*it_estructurales)->get_tipo() == EstructuralUnitario::Casa_Fantasma )
			casas_fantasma.push_back(*it_estructurales);
		++it_estructurales;
	}
	
	return casas_fantasma;
	
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

void MapaImpSet::corregir_posicion(Posicion &p){
   if (p.get_x() < 0)
		p.set_x(p.get_x() + this->ancho);
	else
		if (p.get_x() >= this->ancho)
		   p.set_x(p.get_x() - this->ancho);
	if (p.get_y() < 0)
		p.set_y(p.get_y() + this->alto);
	else
		if (p.get_y() >= this->alto)
			p.set_y(p.get_y() - this->alto);
}
