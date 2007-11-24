#ifndef __COMESTIBLE_FACTORY_H__
#define __COMESTIBLE_FACTORY_H__

#include "Comestible.h"

class ComestibleFactory{
	
	private:
		
		ComestibleFactory(&c);
	
	public:
		enum Tipo_Comestible{PowerUp,Queso,Fruta};
			
		ComestibleFactory();
	
		~ComestibleFactory();
		
		Comestible * construir(Tipo_Comestible &tipo);
		
		
};

#endif /*__COMESTIBLE_FACTORY_H__*/
