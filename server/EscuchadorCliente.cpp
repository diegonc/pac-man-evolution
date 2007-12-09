#include "EscuchadorCliente.h"

#include <iostream>


EscuchadorCliente::EscuchadorCliente(Cliente * c){
	this->cliente = c;
}

EscuchadorCliente::~EscuchadorCliente(){

}

void EscuchadorCliente::run(){
	try{
		S_ptr<Paquete> paquete;
		while(true){
			paquete = cliente->recibir_mensaje();
			//TODO HACER ALGO CON EL PAQUETE
			std::cout << "Leyo un paquete!\n";
		}
	}
	catch(std::runtime_error &e){/*salgo del while*/}
}
