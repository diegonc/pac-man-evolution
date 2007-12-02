#ifndef __CASILLERO_PASILLO_H__
#define __CASILLERO_PASILLO_H__

#include "../common/smart_pointer.h"
#include "Comestible.h"
#include "EstructuralUnitario.h"

class EstructuralPasillo : public EstructuralUnitario{
	private:
		S_ptr<Comestible> comida;
	
		bool salida;
			
	public:
		EstructuralPasillo(Comestible::Enum_Comestible &tipo, Posicion &p);
	
		void ingresar(Jugador& jugador);
	
		~EstructuralPasillo();
	
		char get_tipo();
	
		S_ptr<Comestible> get_comida();
	
		bool es_salida_fantasma();
	
		bool es_salida_pacman();
	
		void set_salida_pacman();
	
};

#endif /*__CASILLERO_PASILLO_H__*/
