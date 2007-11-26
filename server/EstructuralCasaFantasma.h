#ifndef __CASILLERO_CASA_FANSTASMA_H__
#define __CASILLERO_CASA_FANSTASMA_H__

#include "Estructural.h"

class EstructuralCasaFantasma : public Estructural{
				
	public:
		EstructuralCasaFantasma();
	
		void ingresar(Jugador& jugador);
	
		~EstructuralCasaFantasma();
	
		int get_tipo();
};

#endif /*__CASILLERO_CASA_FANSTASMA_H__*/
