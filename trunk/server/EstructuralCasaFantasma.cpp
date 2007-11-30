#include "EstructuralCasaFantasma.h"

#define TIPO_CASA_FANTASMA	1

EstructuralCasaFantasma::EstructuralCasaFantasma(Posicion &p):EstructuralUnitario(p){}
	
void EstructuralCasaFantasma::ingresar(Jugador& jugador){}
	
EstructuralCasaFantasma::~EstructuralCasaFantasma(){}

int EstructuralCasaFantasma::get_tipo(){
	return TIPO_CASA_FANTASMA;
}
