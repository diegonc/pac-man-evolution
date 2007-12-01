#include "EstructuralCasaFantasma.h"

EstructuralCasaFantasma::EstructuralCasaFantasma(Posicion &p):EstructuralUnitario(p){}
	
void EstructuralCasaFantasma::ingresar(Jugador& jugador){}
	
EstructuralCasaFantasma::~EstructuralCasaFantasma(){}

char EstructuralCasaFantasma::get_tipo(){
	return EstructuralUnitario::Casa_Fanstasma;
}
