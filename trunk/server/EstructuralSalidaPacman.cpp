#include "EstructuralSalidaPacman.h"


EstructuralSalidaPacman::EstructuralSalidaPacman(Posicion &p):EstructuralUnitario(p){
	
}
	
void EstructuralSalidaPacman::ingresar(Jugador& jugador){}
	
EstructuralSalidaPacman::~EstructuralSalidaPacman(){}
	
char EstructuralSalidaPacman::get_tipo(){
	return EstructuralUnitario::Salida_Pacman;
		
}
