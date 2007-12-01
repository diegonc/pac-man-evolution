#include "EstructuralCasaFantasma.h"

#include "Fantasma.h"

EstructuralCasaFantasma::EstructuralCasaFantasma(Posicion &p):EstructuralUnitario(p){}
	
void EstructuralCasaFantasma::ingresar(Jugador& jugador){
	try{
		Fantasma fantasma = dynamic_cast<Fantasma& >(*jugador.get_personaje());
		fantasma.revivir();
	}
	catch(std::bad_cast &e){/*No hago nada si no es fantasma*/ }
	
}
	
EstructuralCasaFantasma::~EstructuralCasaFantasma(){}

char EstructuralCasaFantasma::get_tipo(){
	return EstructuralUnitario::Casa_Fanstasma;
}
