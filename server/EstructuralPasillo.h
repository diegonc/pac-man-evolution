#ifndef __CASILLERO_PASILLO_H__
#define __CASILLERO_PASILLO_H__

#include "../common/smart_pointer.h"
#include "Comestible.h"
#include "Estructural.h"

class EstructuralPasillo : public Estructural{
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
