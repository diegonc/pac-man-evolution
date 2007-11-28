#ifndef __PACMAN_H__
#define __PACMAN_H__

#include "Personaje.h"

#include "Jugador.h"
#include "Comestible.h"

class PacMan : public Personaje{
	private:
		bool power_up_activado;
	
	public:
		PacMan(Jugador *jugador);
	
		void comer(Comestible& comestible);
	
		void colision(Jugador& jugador);
	
		void set_power_up(bool activado);
	
		bool tiene_power_up();
	
		Personaje::Enum_Personaje get_tipo();
};

#endif /*__PACMAN_H__*/
