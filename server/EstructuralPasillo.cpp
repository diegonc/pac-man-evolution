#include "EstructuralPasillo.h"

#include "ComestibleFactory.h"

EstructuralPasillo::EstructuralPasillo(Comestible::Enum_Comestible &tipo, Posicion &p):EstructuralUnitario(p){
	//creo la fabrica para agregarle el comestible
	ComestibleFactory fabrica;
	//al comestible le seteo el medio de la posicion de mi casillero
	Posicion pos = p;
	pos.set_x(p.get_x() + 0.5);
	pos.set_y(p.get_y() + 0.5);
	//creo el comestible y lo meto en un smart pointer
	S_ptr<Comestible> comida_a_asignar(fabrica.construir(tipo,pos) );
	//lo asigno
	this->comida = comida_a_asignar;
	//por defecto, pongo que no es salida
	this->salida = false;
	
}
EstructuralPasillo::EstructuralPasillo(Posicion &p):EstructuralUnitario(p){
	this->salida = false;
}
EstructuralPasillo::~EstructuralPasillo(){

}
S_ptr<Comestible> EstructuralPasillo::get_comida(){
	return this->comida; //devuelvo la comida
}
void EstructuralPasillo::ingresar(Jugador& jugador){
	//si la comida no es nula, me fijo que la coman
	if(! this->comida.es_nulo() ){
		//intenta comerla
		bool comio = jugador.comer(*this->comida);
		//si la pudo comer la quito
		if(comio){
			S_ptr<Comestible> comida_nula;
			this->comida = comida_nula;
		}
	}

}

EstructuralUnitario::Enum_Estructural EstructuralPasillo::get_tipo(){
	if(!salida)
		return EstructuralUnitario::Pasillo;
	else
		return EstructuralUnitario::Salida_Pacman;
}
bool EstructuralPasillo::es_salida_pacman(){
	return this->salida;
	
}
void EstructuralPasillo::set_salida_pacman(){
	this->salida = true;
}
