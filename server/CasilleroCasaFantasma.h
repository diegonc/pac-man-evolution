#ifndef __CASILLERO_CASA_FANSTASMA_H__
#define __CASILLERO_CASA_FANSTASMA_H__

#include "Casillero.h"

class CasilleroCasaFantasma : public Casillero{
				
	public:
		CasilleroCasaFantasma();
	
		void ingresar(Jugador *jugador);
	
		~CasilleroCasaFantasma();
};

#endif /*__CASILLERO_CASA_FANSTASMA_H__*/
