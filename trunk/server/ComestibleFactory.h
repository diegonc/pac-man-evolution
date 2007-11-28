#ifndef __COMESTIBLE_FACTORY_H__
#define __COMESTIBLE_FACTORY_H__

#include "Comestible.h"

class ComestibleFactory{
	
	private:
	
		ComestibleFactory(ComestibleFactory &c);
	
	public:
			
		ComestibleFactory();
	
		~ComestibleFactory();
		
		Comestible * construir(Comestible::Enum_Comestible tipo);
		
		
};

#endif /*__COMESTIBLE_FACTORY_H__*/
