#ifndef __POWER_UP_H__
#define __POWER_UP_H__

#include "Comestible.h"
#include "Personaje.h"

#define PUNTOS_POWER_UP		-5

class PowerUp : public Comestible{
	public:
		PowerUp();
		
		~PowerUp();
	
		void afectar_personaje(Personaje& personaje);
		
};

#endif /*__POWER_UP_H__*/
