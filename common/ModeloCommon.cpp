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
	
	std::list< S_ptr<Jugador> >::iterator it_jugadores = this->jugadores.begin();
	
	S_ptr<Jugador> resultado_busqueda;
	bool encontro = false;
	
	while( (it_jugadores != this->jugadores.end()) && (!encontro) ){
		if( (*it_jugadores)->get_id() == id){
			encontro = true;
			resultado_busqueda = *it_jugadores;
		}
		it_jugadores++;
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
