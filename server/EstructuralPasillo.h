#ifndef __CASILLERO_PASILLO_H__
#define __CASILLERO_PASILLO_H__

#include "../common/smart_pointer.h"
#include "Comestible.h"
#include "EstructuralUnitario.h"

class EstructuralPasillo : public EstructuralUnitario{
	private:
		S_ptr<Comestible> comida;
			
	public:
		EstructuralPasillo(Comestible::Enum_Comestible &tipo);
	
		void ingresar(Jugador& jugador);
	
		~EstructuralPasillo();
	
		int get_tipo();
	
		S_ptr<Comestible> get_comida();
	
};

#endif /*__CASILLERO_PASILLO_H__*/
