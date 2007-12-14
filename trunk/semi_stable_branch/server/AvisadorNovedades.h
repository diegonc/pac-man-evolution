#ifndef __AVISADOR_NOVEDADES_H__
#define __AVISADOR_NOVEDADES_H__

#include "../common/thread.h"
#include "../common/observador.h"
#include "../common/smart_pointer.h"
#include "../common/Comestible.h"
#include "PaqueteStatus.h"
#include "../common/EscritorCliente.h"
#include "../common/NovedadComestible.h"
#include "../common/mutex.h"
#include <list>
#include "ClientPool.h"

class AvisadorNovedades : public Thread,public Observador{
	
	private:
		Mutex llave;

		ClientPool * clientes;
		
		std::list< NovedadComestible > novedades_comestible;
	
		bool _parar;
	public:
		
		AvisadorNovedades(ClientPool * clientes);
	
		~AvisadorNovedades();
	
		void run();
	
		void parar();
		
		void actualizar(Observable* Obs,void * Novedad);
};


#endif /*__AVISADOR_NOVEDADES_H__*/
