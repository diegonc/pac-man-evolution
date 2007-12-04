#include "EstructuralCasaFantasma.h"

#include "Fantasma.h"

EstructuralCasaFantasma::EstructuralCasaFantasma(Posicion &p):EstructuralUnitario(p){}
	
void EstructuralCasaFantasma::ingresar(Jugador& jugador){
	try{
		//trata de hacer un cast del personaje del jugador y si es fantasma
		//lo revive, en caso contrario no hace nada
		Fantasma fantasma = dynamic_cast<Fantasma& >(*jugador.get_personaje());
		fantasma.revivir();
	}
	catch(std::bad_cast &e){/*No hago nada si no es fantasma*/ }
	
}
	
EstructuralCasaFantasma::~EstructuralCasaFantasma(){}

EstructuralUnitario::Enum_Estructural EstructuralCasaFantasma::get_tipo(){
	return EstructuralUnitario::Casa_Fanstasma;
}
bool EstructuralCasaFantasma::es_casa_fantasma(){
	return true;
}
