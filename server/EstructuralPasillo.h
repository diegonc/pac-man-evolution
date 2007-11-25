#ifndef __CASILLERO_PASILLO_H__
#define __CASILLERO_PASILLO_H__

#include "ComestibleFactory.h"
#include "../common/smart_pointer.h"
#include "Comestible.h"
#include "Estructural.h"

class CasilleroPasillo : public Estructural{
	private:
		Comestible *comida;
			
	public:
		CasilleroPasillo(ComestibleFactory::Tipo_Comestible &tipo);
	
		void ingresar(Jugador *jugador);
	
		~CasilleroPasillo();
	
		int get_tipo();
	
};

#endif /*__CASILLERO_PASILLO_H__*/
