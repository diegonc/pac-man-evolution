#include "AvisadorNovedades.h"


AvisadorNovedades::AvisadorNovedades(ClientPool * clientes){
	this->clientes = clientes;
}
AvisadorNovedades::~AvisadorNovedades(){
		
}

void AvisadorNovedades::run(){
	_parar = false;	
	
	std::list<Cliente*>::const_iterator it;
	
	while (! _parar ){

		llave.lock();
		S_ptr<Paquete> paquete_status(new PaqueteStatus(&novedades_comestible));
		novedades_comestible.clear();
		llave.unlock();
		
		std::list<Cliente*> lista_clientes = clientes->get_clientes();
		it = lista_clientes.begin();
		while( it != lista_clientes.end() ){
			try{
				(*it)->get_escritor().encolar_paquete(paquete_status); 
				//(*it)->enviar_mensaje(paquete_status);
			 	++it;
			}
			catch(std::runtime_error &e){
				std::cout << "Entro aca (client pool)\n";
				clientes->quitar_cliente( (*it)->get_id() );
			}
		}
		
		
		usleep(10000);
	}	
}
void AvisadorNovedades::parar(){
	_parar = true;
}

void AvisadorNovedades::actualizar(Observable* Obs,void * Novedad){
   	if (Novedad!=NULL){
      	NovedadComestible* novedadComest = (NovedadComestible*) Novedad;
	   	llave.lock();
	   	novedades_comestible.push_back(*novedadComest);
	   	llave.unlock();
    }
}