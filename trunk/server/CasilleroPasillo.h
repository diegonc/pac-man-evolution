#ifndef __CASILLERO_PASILLO_H__
#define __CASILLERO_PASILLO_H__

#include "../common/smart_pointer.h"
#include "Comestible.h"
#include "ComestibleFactory.h"
#include "Casillero.h"

class CasilleroPasillo : public Casillero{
	private:
		Comestible *comida;
	public:
		CasilleroPasillo(Tipo_Comestible &tipo);
	
		void ingresar(Jugador *jugador);
	
		~CasilleroPasillo();
};

#endif /*__CASILLERO_PASILLO_H__*/
