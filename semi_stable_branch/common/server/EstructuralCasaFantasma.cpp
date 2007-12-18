#include <server/EstructuralCasaFantasma.h>

#include <server/Fantasma.h>

EstructuralCasaFantasma::EstructuralCasaFantasma(Posicion &p):EstructuralUnitario(p){}
	
void EstructuralCasaFantasma::ingresar(Jugador& jugador){
	//trata de hacer un cast del personaje del jugador y si es fantasma
	//lo revive, en caso contrario no hace nada
	Fantasma * fantasma = dynamic_cast<Fantasma* >(&(*jugador.get_personaje()));
	if(fantasma != NULL)
		fantasma->revivir();
}
	
EstructuralCasaFantasma::~EstructuralCasaFantasma(){}

EstructuralUnitario::Enum_Estructural EstructuralCasaFantasma::get_tipo(){
	return EstructuralUnitario::Casa_Fantasma;
}
bool EstructuralCasaFantasma::es_casa_fantasma(){
	return true;
}
