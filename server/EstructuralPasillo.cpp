#include "CasilleroPasillo.h"

CasilleroPasillo::CasilleroPasillo(ComestibleFactory::Tipo_Comestible &tipo){
	ComestibleFactory fabrica;
	
	this->comida = fabrica.construir(tipo); 	
}

CasilleroPasillo::~CasilleroPasillo(){
	if(this->comida != 0)
		delete this->comida;		
}

void CasilleroPasillo::ingresar(Jugador *jugador){
	jugador->comer(this->comida);
	this->comida = 0;
}

int get_tipo(){
	return -1;//no tiene tipo
}
