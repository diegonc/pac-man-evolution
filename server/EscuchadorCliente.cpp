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
			std::cout << "Entro al escuchador\n";
			op->ejecutar(*(ModeloServidor::get_instancia()));
			std::cout << "Ejecuto la operacion\n";
			delete op;
		}
	}
	catch(std::runtime_error &e){/*salgo del while*/
		std::cout << "Bardeao el run del escuchador\n";	
	}
}
