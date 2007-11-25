#ifndef __COMPARADOR_POSICION_H__
#define __COMPARADOR_POSICION_H__

#include "MapaImpMatriz.h"

class ComparadorPosicion{
	
	public:
		bool operator()(Elemento &e1, Elemento &e2){
			if(e1.posicion == e2.posicion )
				return true;
			else
				return false;
		}
};

#endif /*__COMPARADOR_POSICION_H__*/
