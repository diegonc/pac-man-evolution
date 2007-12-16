#include "EscritorCliente.h"

#define _INTERVALO_STATUS	3 //segundos

EscritorCliente::EscritorCliente(Cliente * c){
	this->cliente = c;
	this->debe_terminar = false;
}

EscritorCliente::~EscritorCliente(){

}

void EscritorCliente::run(){
	try{
		while(!debe_terminar){
			if(! buffer.empty() ){
				Bloqueo b(&llave);
				cliente->enviar_mensaje(buffer.front());
				buffer.pop();
			}
			else{
				this->e.esperar_activacion();
			}
		}
	}
	catch(std::runtime_error &e){
		/* Si hubo error de lectura es porque el cliente se desconecto, asi que lo hago terminar. */
		this->cliente->terminar();
	}
}

void EscritorCliente::terminar(){
	this->debe_terminar = true;
	//Aviso a los observadores que el cliente se desconecto
	this->set_cambio();
	this->avisar_observadores(this->cliente);
}	

void EscritorCliente::encolar_paquete(S_ptr<Paquete> paquete){
	{
		Bloqueo bloqueo(&llave);//bloqueo por si acceden de desde diferentes threads
		buffer.push(paquete);
	}
	this->e.lanzar_evento();
}
