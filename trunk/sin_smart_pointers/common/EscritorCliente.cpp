#include "EscritorCliente.h"

#define _INTERVALO_STATUS	3 //segundos

EscritorCliente::EscritorCliente(Cliente * c){
	this->cliente = c;
	this->debe_terminar = false;
}

EscritorCliente::~EscritorCliente(){

}

void EscritorCliente::run(){
	Paquete * paquete = NULL;
	try{
		while(!debe_terminar){
			if(! buffer.empty() ){
				Bloqueo b(&llave);
				paquete = buffer.front();
				cliente->enviar_mensaje(paquete);
				buffer.pop();
			}
			else{
				this->e.esperar_activacion();
			}
		}
	}
	catch(std::runtime_error &e){
		/* Si hubo error de lectura es porque el cliente se desconecto, asi que lo hago terminar. */
		this->terminar();
	}
   std::cout << "Termina el escritor\n";
}

void EscritorCliente::terminar(){
	this->debe_terminar = true;
	//Aviso a los observadores que el cliente se desconecto
	this->set_cambio();
	this->avisar_observadores(this->cliente);
}	

void EscritorCliente::encolar_paquete(Paquete * paquete){
	{
		Bloqueo bloqueo(&llave);//bloqueo por si acceden de desde diferentes threads
		buffer.push(paquete);
	}
	this->e.lanzar_evento();
}
