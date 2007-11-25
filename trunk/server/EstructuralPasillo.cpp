#include "EstructuralPasillo.h"

EstructuralPasillo::EstructuralPasillo(ComestibleFactory::Tipo_Comestible &tipo){
	ComestibleFactory fabrica;
	
	this->comida = fabrica.construir(tipo); 	
}

EstructuralPasillo::~EstructuralPasillo(){
	if(this->comida != 0)
		delete this->comida;		
}

void EstructuralPasillo::ingresar(Jugador *jugador){
	jugador->comer(this->comida);
	this->comida = 0;
}

int get_tipo(){
	return -1;//no tiene tipo
}
