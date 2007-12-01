#ifndef __FANTASMA_H__
#define __FANTASMA_H__

#include "Personaje.h"

class Fantasma : public Personaje{
	public:
		Fantasma(Jugador *jugador);	
	
		void comer(Comestible& comestible);
	
		void colision(Jugador& jugador);
	
		Enum_Personaje get_tipo();
	
	
		int get_velocidad();
};

#endif /*__FANTASMA_H__*/