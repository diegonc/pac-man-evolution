#include "AvisadorNovedades.h"

#include "PaqueteStatus.h"
#include "EscritorCliente.h"

AvisadorNovedades::AvisadorNovedades(ClientPool * clientes){
	this->clientes = clientes;
}
AvisadorNovedades::~AvisadorNovedades(){
		
}

void AvisadorNovedades::run(){
	
	
	std::list<Cliente*>::const_iterator it;
	
	while (! _parar ){
		S_ptr<Paquete> paquete_status(new PaqueteStatus());
		
		it = clientes->get_clientes().begin();
		while( it != clientes->get_clientes().end() ){
			(*it)->get_escritor().encolar_paquete(paquete_status); 
			 ++it;
		}
		usleep(10000);
	}	
}
void AvisadorNovedades::parar(){
	_parar = true;
}
