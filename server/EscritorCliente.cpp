#include "EscritorCliente.h"

#define _INTERVALO_STATUS	3 //segundos


#include <iostream> //TODO SACARRR

EscritorCliente::EscritorCliente(Cliente * c){
	this->cliente = c;
	this->debe_terminar = false;
}

EscritorCliente::~EscritorCliente(){

}

void EscritorCliente::run(){
	try{
		S_ptr<Paquete> paquete;
		while(!debe_terminar){
			
		}
	}
	catch(std::runtime_error &e){
		throw e;	
	}
}

void EscritorCliente::terminar(){
	this->debe_terminar = true;
}	

void EscritorCliente::encolar_paquete(S_ptr<Paquete> paquete){
	Bloqueo bloqueo(&llave);//bloqueo por si acceden de desde diferentes threads
	buffer.push(paquete);
}
