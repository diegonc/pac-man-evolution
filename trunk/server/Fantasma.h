#ifndef __FANTASMA_H__
#define __FANTASMA_H__

#include "Personaje.h"

class Fantasma : public Personaje{
	public:
		void comer(Jugador& jugador, Comestible& comestible);
	
		void colision(Jugador& jugador);
};

#endif /*__FANTASMA_H__*/
