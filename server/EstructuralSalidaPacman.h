/*#ifndef __ESTRUCTURAL_SALIDA_PACMAN_H__
#define __ESTRUCTURAL_SALIDA_PACMAN_H__


#include "../common/smart_pointer.h"
#include "EstructuralUnitario.h"

class EstructuralSalidaPacman : public EstructuralUnitario{
	private:
		S_ptr<Comestible> comida;
			
	public:
		EstructuralSalidaPacman(Posicion &p);
	
		void ingresar(Jugador& jugador);
	
		~EstructuralSalidaPacman();
	
		char get_tipo();

};

#endif /*__ESTRUCTURAL_SALIDA_PACMAN_H__*/*/
