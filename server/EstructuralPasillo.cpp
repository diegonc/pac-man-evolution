#include "EstructuralPasillo.h"

#include <iostream>

EstructuralPasillo::EstructuralPasillo(ComestibleFactory::Tipo_Comestible &tipo){
	ComestibleFactory fabrica;
	S_ptr<Comestible> comida_a_asignar(fabrica.construir(tipo));
	
	this->comida = comida_a_asignar;
}

EstructuralPasillo::~EstructuralPasillo(){
	/*if(this->comida != 0)
		delete this->comida;		*/
}

void EstructuralPasillo::ingresar(Jugador& jugador){
	jugador.comer(*this->comida);
	
	S_ptr<Comestible> comida_nula;
	
	this->comida = comida_nula;
	/*delete this->comida;
	
	this->comida = 0;*/
}

int EstructuralPasillo::get_tipo(){
	return -1;//no tiene tipo
}
