#include "EscuchadorCliente.h"

#ifndef PROGRAMA_CLIENTE
   #include "../server/ModeloServidor.h"
#else
   #include "../client/ModeloServidor.h"
#endif



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
			//std::cout << "Recibi un paquete " << (int) paquete->get_tipo();
			op = paquete->get_operacion();
			op->ejecutar(*(ModeloServidor::get_instancia()));
			//std::cout << " y la ejecuto piola\n";
			delete op;
		}
	}
	catch(std::runtime_error &e){
		throw e;
		/*salgo del while*/}
}
