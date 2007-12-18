#include "EstructuralPasillo.h"

#include "ComestibleFactory.h"

EstructuralPasillo::EstructuralPasillo(Comestible::Enum_Comestible &tipo, Posicion &p):EstructuralUnitario(p){
	set_comida( tipo );
	//por defecto, pongo que no es salida
	this->salida = false;
	
	
}
EstructuralPasillo::EstructuralPasillo(Posicion &p):EstructuralUnitario(p){
	this->salida = false;
	this->comida=NULL;
}
EstructuralPasillo::~EstructuralPasillo(){
	if (this->comida!=NULL)
		delete this->comida;
}

void EstructuralPasillo::set_comida( Comestible::Enum_Comestible& tipo )
{
	//creo la fabrica para agregarle el comestible
	ComestibleFactory fabrica;
	//al comestible le seteo el medio de la posicion de mi casillero
	Posicion pos( get_posicion() );
	pos.set_x(pos.get_x() + 0.5);
	pos.set_y(pos.get_y() + 0.5);
	//creo el comestible y lo meto en un smart pointer
	Comestible * comida_a_asignar = fabrica.construir(tipo,pos) ;
	//lo asigno
	this->comida = comida_a_asignar;
}

Comestible * EstructuralPasillo::get_comida(){
	return this->comida; //devuelvo la comida
}
void EstructuralPasillo::ingresar(Jugador& jugador){
	//si la comida no es nula, me fijo que la coman
	if(! this->comida->es_invalido() ){
		//intenta comerla
		bool comio = jugador.comer(*this->comida);
		//si la pudo comer la quito
		if(comio){
			this->comida->set_invalido();
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

void EstructuralPasillo::set_comida( Comestible * comida_nueva){
	if(comida_nueva != NULL){	
		comida_nueva->get_posicion().set_x(this->get_posicion().get_x() + 0.5);
		comida_nueva->get_posicion().set_y(this->get_posicion().get_y() + 0.5);
		
	}
	if(this->comida != NULL)
		delete	this->comida;
	this->comida = comida_nueva;
}