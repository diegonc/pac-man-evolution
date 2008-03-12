#include "ModeloServidor.h"

ModeloServidor::ModeloServidor() : ModeloCommon(){
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

