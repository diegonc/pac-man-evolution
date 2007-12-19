#include <server/EscuchadorCliente.h>
#include <server/ModeloCommon.h>

const int EscuchadorCliente::SENIAL_CANCELAR = SIGUSR2;

void EscuchadorCliente::manejador_signal(int num_signal){

	switch(num_signal){
		case EscuchadorCliente::SENIAL_CANCELAR: 
         		std::cout << "entro a SIGUSR2" << std::endl << std::flush;
      break;
		
		default: raise(num_signal);				
	}
}
void EscuchadorCliente::set_propiedades_signal(const int id_signal){
	//Setteo propiedades para la accion a realizarse con una señal
		this->accion_signal.sa_handler = manejador_signal;
		sigemptyset(&this->accion_signal.sa_mask);
		this->accion_signal.sa_flags = 0;//~SA_RESTART;
		sigaction(id_signal,&this->accion_signal, NULL);
	
}


EscuchadorCliente::EscuchadorCliente(Cliente * c){
	this->cliente = c;
	set_propiedades_signal(EscuchadorCliente::SENIAL_CANCELAR);
}

EscuchadorCliente::~EscuchadorCliente(){

}

void EscuchadorCliente::run(){
	
   static int j = 0;

	bool correr = true;
	
	S_ptr<Paquete> paquete;
	Operacion * op;

	while(correr){
		try{
			paquete = cliente->recibir_mensaje();
			if(! paquete.es_nulo() ){            
            j++;	
            op = paquete->get_operacion();
            if (op != NULL) {				
               op->ejecutar(cliente->get_modelo());
				   delete op;
            }
			}
		}
		catch(std::runtime_error &e){
			correr = false;
		}	
	}
	sigaction(NULL,&this->accion_signal, NULL);
   std::cout << "Termina el escuchador\n";
}

