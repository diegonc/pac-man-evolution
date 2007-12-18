#include "EscuchadorCliente.h"
#include "ModeloCommon.h"

EscuchadorCliente::EscuchadorCliente(Cliente * c){
	this->cliente = c;
}

EscuchadorCliente::~EscuchadorCliente(){

}

void EscuchadorCliente::run(){
	
   static int j = 0;

	bool correr = true;
	
	Paquete * paquete = NULL;
	Operacion * op;

	while(correr){
		try{
			paquete = cliente->recibir_mensaje();
			if(paquete != NULL ){
				//std::cout << "Recibiendo: " << (int) paquete->get_tipo() << std::endl << std::flush;
				j++;	
				op = paquete->get_operacion();
				if (op != NULL) {				
				   op->ejecutar(cliente->get_modelo());
					   delete op;
				}
				//delete paquete;
			}
		}
		catch(std::runtime_error &e){
			correr = false;
		}	
	}
   std::cout << "Termina el escuchador\n";
}
