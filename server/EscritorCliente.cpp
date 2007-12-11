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
		while(!debe_terminar){
			//std::cout << "Hay " << buffer.size() <<"\n";
			if(! buffer.empty() ){
				//std::cout << "Manda mensaje\n";
				Bloqueo b(&llave);
				cliente->enviar_mensaje(buffer.front());
				buffer.pop();
			}
			else{
				//std::cout << "Bloquea\n";
				this->e.esperar_activacion();
			}
		}
	}
	catch(std::runtime_error &e){
		throw e;	
	}
}

void EscritorCliente::terminar(){
	this->debe_terminar = true;
	this->e.lanzar_evento();
}	

void EscritorCliente::encolar_paquete(S_ptr<Paquete> paquete){
	{
		Bloqueo bloqueo(&llave);//bloqueo por si acceden de desde diferentes threads
		buffer.push(paquete);
	}
	this->e.lanzar_evento();
}
