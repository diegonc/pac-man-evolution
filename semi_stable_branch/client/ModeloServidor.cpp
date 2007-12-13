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
