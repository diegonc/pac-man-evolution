#include "EscuchadorCliente.h"

#include "ModeloServidor.h"



EscuchadorCliente::EscuchadorCliente(Cliente * c){
	this->cliente = c;
}

EscuchadorCliente::~EscuchadorCliente(){

}

void EscuchadorCliente::run(){
	try{
		S_ptr<Paquete> paquete;
		Operacion * op;
		while(true){
			paquete = cliente->recibir_mensaje();
			op = paquete->get_operacion();
			op->ejecutar(*(ModeloServidor::get_instancia()));
		}
	}
	catch(std::runtime_error &e){/*salgo del while*/}
}
