#include "AvisadorNovedades.h"
#include "ModeloServidor.h"

AvisadorNovedades::AvisadorNovedades(ClientPool * clientes){
	this->clientes = clientes;
}
AvisadorNovedades::~AvisadorNovedades(){
		
}

void AvisadorNovedades::borrar_novedades_acumuladas(){
	llave.lock();	
	novedadesAcumuladas.clear();
	llave.unlock();
}

bool AvisadorNovedades::mandar_todo(){
	_MandarTodo=true;
}



void AvisadorNovedades::run(){
	_parar = false;	
	
	std::list<Cliente*>::const_iterator it;

	while (! _parar ){
		S_ptr<Paquete> paquete_status;
		llave.lock();		
		//si no tiene q mandar todos los comestibles
		if (!_MandarTodo){
			//creo el paquete con las novedades actuales
			paquete_status=new PaqueteStatus(&novedades_comestible,ModeloServidor::get_instancia());
			//appendeo las novedades actuales a las acumuladas
			novedadesAcumuladas.splice (novedadesAcumuladas.end(), novedades_comestible);
		}else{ //tengo q mandar todas las novedades
			//appendeo las novedades actuales
			novedadesAcumuladas.splice (novedadesAcumuladas.end(), novedades_comestible);
			//mando todas las novedades q capture
			paquete_status=new PaqueteStatus(&novedadesAcumuladas,ModeloServidor::get_instancia());
		}
		_MandarTodo=false;
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
