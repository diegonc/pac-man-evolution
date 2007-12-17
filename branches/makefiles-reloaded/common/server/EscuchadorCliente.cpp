#include <server/EscuchadorCliente.h>
#include <server/ModeloCommon.h>

EscuchadorCliente::EscuchadorCliente(Cliente * c){
	this->cliente = c;
}

EscuchadorCliente::~EscuchadorCliente(){

}

void EscuchadorCliente::run(){
	
	bool correr = true;
	
	S_ptr<Paquete> paquete;
	Operacion * op;

	while(correr){
		try{
			paquete = cliente->recibir_mensaje();
			if(! paquete.es_nulo() ){
				op = paquete->get_operacion();
				op->ejecutar(cliente->get_modelo());
				delete op;
			}
		}
		catch(std::runtime_error &e){
			correr = false;
		}	
	}
   std::cout << "Termina el escuchador\n";
}

