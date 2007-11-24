#ifndef __COMESTIBLE_FACTORY_H__
#define __COMESTIBLE_FACTORY_H__

#include "Comestible.h"

class ComestibleFactory{
	
	private:
	
		ComestibleFactory(ComestibleFactory &c);
	
	public:
		
		enum Tipo_Comestible{power_up,quesito,frutita};	
				
		ComestibleFactory();
	
		~ComestibleFactory();
		
		Comestible * construir(Tipo_Comestible &tipo);
		
		
};

#endif /*__COMESTIBLE_FACTORY_H__*/
