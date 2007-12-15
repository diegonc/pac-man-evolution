#include "ModeloCommon.h"

ModeloCommon::ModeloCommon(){
	//cargar_modelo(); // provisorio
	MundoBasicImp * m = new MundoBasicImp();
	S_ptr<MundoBajoNivel> mundo_default(m);
	this->set_mundo(mundo_default);

}

void ModeloCommon::set_mundo(S_ptr<MundoBajoNivel> mundo){
	this->mundo = mundo;
	
	//this->mundo->get_mapa_activo().agregar_observador(this);
}
ModeloCommon::~ModeloCommon(){
}

void ModeloCommon::agregar_jugador(Jugador * jugador){
	Bloqueo b(&llave);	
   //lo agrego a los jugadores
	this->jugadores.push_back(jugador);
	
}

const std::list<Jugador *> ModeloCommon::get_jugadores(){
  	Bloqueo b(&llave);
   return this->jugadores;
}
Jugador * ModeloCommon::get_jugador(unsigned int id){
	
	std::list< Jugador * > lista_jugadores = this->get_jugadores();
	std::list< Jugador * >::iterator it_jugadores = lista_jugadores.begin();
	
	Jugador * resultado_busqueda = NULL;
	bool encontro = false;
	
	while( (it_jugadores != lista_jugadores.end()) && (!encontro) ){
		if( (*it_jugadores)->get_id() == id){
			encontro = true;
			resultado_busqueda = *it_jugadores;
		}
		it_jugadores++;
	}
	return resultado_busqueda;
}
void ModeloCommon::quitar_jugador(unsigned int id){
	std::list< Jugador *> lista_jugadores = get_jugadores();
   std::list< Jugador * >::iterator it_jugadores = lista_jugadores.begin();
	
	bool encontro = false;
	
	while( (it_jugadores != lista_jugadores.end()) && (!encontro) ){
		if( (*it_jugadores)->get_id() == id){
			encontro = true;
			jugadores.erase(it_jugadores);
		}
		it_jugadores++;
	}
}
	
MundoBajoNivel& ModeloCommon::get_mundo(){
	return *this->mundo;
}
bool ModeloCommon::esta_terminado(){
	return this->termino;
}
void ModeloCommon::set_cargado(){
	this->set_cambio();
	this->avisar_observadores(NULL);
}
