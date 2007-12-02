#ifndef __CASILLERO_CASA_FANSTASMA_H__
#define __CASILLERO_CASA_FANSTASMA_H__

#include "EstructuralUnitario.h"

class EstructuralCasaFantasma : public EstructuralUnitario{
				
	public:
		EstructuralCasaFantasma(Posicion &p);
	
		void ingresar(Jugador& jugador);
	
		~EstructuralCasaFantasma();
	
		char get_tipo();
	
		bool es_casa_fantasma();
};

#endif /*__CASILLERO_CASA_FANSTASMA_H__*/
