#include "ModeloCommon.h"

ModeloCommon::ModeloCommon(){
	//cargar_modelo(); // provisorio
	MundoBasicImp * m = new MundoBasicImp();
	S_ptr<MundoBajoNivel> mundo_default(m);
	this->set_mundo(mundo_default);
	this->parar = false;
}

void ModeloCommon::set_mundo(S_ptr<MundoBajoNivel> mundo){
	this->mundo = mundo;
	
	//this->mundo->get_mapa_activo().agregar_observador(this);
}
ModeloCommon::~ModeloCommon(){
}

void ModeloCommon::agregar_jugador(Tipo_Jugador jugador){
	
	//lo agrego a los jugadores
	this->jugadores.push_back(jugador);
	
}

const std::list<S_ptr<Jugador> >& ModeloCommon::get_jugadores(){
	return this->jugadores;
}
S_ptr<Jugador> ModeloCommon::get_jugador(int id){
	
	std::list< S_ptr<Jugador> >::iterator it_jugadores;
	
	S_ptr<Jugador> resultado_busqueda;
	
	for(it_jugadores = this->jugadores.begin(); 
		it_jugadores != this->jugadores.end(); it_jugadores++){
		
		if( (*it_jugadores)->get_id() == id)
			resultado_busqueda = *it_jugadores;
	}
	return resultado_busqueda;
}
	
MundoBajoNivel& ModeloCommon::get_mundo(){
	return *this->mundo;
}
void ModeloCommon::actualizar(Observable * observable, void * param){
	this->parar = true;
}
bool ModeloCommon::esta_terminado(){
	return this->termino;
}
void ModeloCommon::set_cargado(){
	this->set_cambio();
	this->avisar_observadores(NULL);
}
