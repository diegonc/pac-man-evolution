#include "EstructuralPasillo.h"

#include "ComestibleFactory.h"

EstructuralPasillo::EstructuralPasillo(Comestible::Enum_Comestible &tipo){
	ComestibleFactory fabrica;
	Posicion p = this->get_posicion();
	p.set_x(p.get_x() + 0.5);
	p.set_y(p.get_y() + 0.5);
	S_ptr<Comestible> comida_a_asignar(fabrica.construir(tipo,p) );
	
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
	/*delete this->comida;
	
	this->comida = 0;*/
}

int EstructuralPasillo::get_tipo(){
	return -1;//no tiene tipo
}
