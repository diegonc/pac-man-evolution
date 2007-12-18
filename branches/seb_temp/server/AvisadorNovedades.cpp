#include "AvisadorNovedades.h"
#include "ModeloServidor.h"

AvisadorNovedades::AvisadorNovedades(ClientPool * clientes){
	this->clientes = clientes;
}
AvisadorNovedades::~AvisadorNovedades(){
		
}

void AvisadorNovedades::run(){
	_parar = false;	
	
	std::list<Cliente*>::const_iterator it;
	std::cout << "Soy: " << pthread_self() << "<--- AVISADOR " << std::endl << std::flush;
	while (! _parar ){

		llave.lock();
		S_ptr<Paquete> paquete_status(new PaqueteStatus(&novedades_comestible,ModeloServidor::get_instancia()));
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
				std::cout << "QuitarCliente AvisadorNovedades (client pool)\n";
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
