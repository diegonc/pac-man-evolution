#ifndef __AVISADOR_NOVEDADES_H__
#define __AVISADOR_NOVEDADES_H__

#include "../common/thread.h"
#include "ClientPool.h"

class AvisadorNovedades : public Thread{
	
	private:
		ClientPool * clientes;
	
		bool _parar;
	public:
		
		AvisadorNovedades(ClientPool * clientes);
	
		~AvisadorNovedades();
	
		void run();
	
		void parar();
};


#endif /*__AVISADOR_NOVEDADES_H__*/
