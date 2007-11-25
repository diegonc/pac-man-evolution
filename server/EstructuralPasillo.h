#ifndef __CASILLERO_PASILLO_H__
#define __CASILLERO_PASILLO_H__

#include "ComestibleFactory.h"
#include "../common/smart_pointer.h"
#include "Comestible.h"
#include "Estructural.h"

class EstructuralPasillo : public Estructural{
	private:
		Comestible *comida;
			
	public:
		EstructuralPasillo(ComestibleFactory::Tipo_Comestible &tipo);
	
		void ingresar(Jugador *jugador);
	
		~EstructuralPasillo();
	
		int get_tipo();
	
};

#endif /*__CASILLERO_PASILLO_H__*/
