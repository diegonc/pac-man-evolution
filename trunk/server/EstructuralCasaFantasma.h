#ifndef __CASILLERO_CASA_FANSTASMA_H__
#define __CASILLERO_CASA_FANSTASMA_H__

#include "EstructuralUnitario.h"

class EstructuralCasaFantasma : public EstructuralUnitario{
				
	public:
		EstructuralCasaFantasma(Posicion &p);
	
		void ingresar(Jugador& jugador);
	
		~EstructuralCasaFantasma();
	
		int get_tipo();
};

#endif /*__CASILLERO_CASA_FANSTASMA_H__*/
