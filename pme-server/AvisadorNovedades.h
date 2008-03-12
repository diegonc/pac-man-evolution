#ifndef __AVISADOR_NOVEDADES_H__
#define __AVISADOR_NOVEDADES_H__

#include <common/thread.h>
#include <common/observador.h>
#include <common/smart_pointer.h>
#include <server/Comestible.h>
#include "PaqueteStatus.h"
#include <server/EscritorCliente.h>
#include <server/NovedadComestible.h>
#include <common/mutex.h>
#include <list>
#include "ClientPool.h"

class AvisadorNovedades : public Thread,public Observador{
	
	private:
		
		Mutex llave;

		ClientPool * clientes;
		
		std::list< NovedadComestible > novedades_comestible;

		std::list< NovedadComestible > novedadesAcumuladas;
	
		bool _parar;

		bool _MandarTodo;
	
	public: 
		
		
		AvisadorNovedades(ClientPool * clientes);
	
		~AvisadorNovedades();
	
		void run();
	
		void parar();

		void borrar_novedades_acumuladas();

		bool mandar_todo();
		
		void actualizar(Observable* Obs,void * Novedad);
};


#endif /*__AVISADOR_NOVEDADES_H__*/
