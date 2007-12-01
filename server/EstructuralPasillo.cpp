#include "EstructuralPasillo.h"

#include "ComestibleFactory.h"

EstructuralPasillo::EstructuralPasillo(Comestible::Enum_Comestible &tipo, Posicion &p):EstructuralUnitario(p){
	ComestibleFactory fabrica;
	Posicion pos = p;
	pos.set_x(p.get_x() + 0.5);
	pos.set_y(p.get_y() + 0.5);
	S_ptr<Comestible> comida_a_asignar(fabrica.construir(tipo,pos) );
	
	this->comida = comida_a_asignar;
}

EstructuralPasillo::~EstructuralPasillo(){

}
S_ptr<Comestible> EstructuralPasillo::get_comida(){
	return this->comida;	
}
void EstructuralPasillo::ingresar(Jugador& jugador){
	if(! this->comida.es_nulo() ){
		jugador.comer(*this->comida);
		
		S_ptr<Comestible> comida_nula;
	
		this->comida = comida_nula;
	}

}

char EstructuralPasillo::get_tipo(){
	return -1;//no tiene tipo
}
