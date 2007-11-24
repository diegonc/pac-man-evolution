#include "CasilleroPasillo.h"

CasilleroPasillo::CasilleroPasillo(Tipo_Comestible& tipo){
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
