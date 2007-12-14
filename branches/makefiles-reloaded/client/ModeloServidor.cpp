#include "ModeloServidor.h"

ModeloServidor::ModeloServidor(){
	//cargar_modelo(); // provisorio
	MundoBasicImp * m = new MundoBasicImp();
	S_ptr<MundoBajoNivel> mundo_default(m);
	this->set_mundo(mundo_default);
	this->parar = false;
}

S_ptr<ModeloServidor> ModeloServidor::instancia;

S_ptr<ModeloServidor> ModeloServidor::get_instancia(){
	if( instancia.es_nulo())
		instancia = S_ptr<ModeloServidor>(new ModeloServidor());
	return instancia;
}

ModeloServidor::~ModeloServidor(){
}

void ModeloServidor::run(){
	
}
void ModeloServidor::quitar_jugador(unsigned int id){
	std::list< S_ptr<Jugador> >::iterator it_jugadores = this->jugadores.begin();
	
	S_ptr<Jugador> resultado_busqueda;
	bool encontro = false;
	
	while( (it_jugadores != this->jugadores.end()) && (!encontro) ){
		if( (*it_jugadores)->get_id() == id){
			encontro = true;
			jugadores.erase(it_jugadores);
		}
		it_jugadores++;
	}
}
