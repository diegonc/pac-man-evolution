#ifndef __POWER_UP_H__
#define __POWER_UP_H__

/**
*	@brief	Esta clase es un comestible que modifica el comportamiento del pacman
*/

#include "Comestible.h"
#include "Personaje.h"

//definicion
#define PUNTOS_POWER_UP		-5

class PowerUp : public Comestible{
	public:
		/**
		*	@brief	Constructor
		*
		*	@param p Posicion del powerUp
		*/
		PowerUp(Posicion &p);
		
		/**
		*	@brief 	Destructor
		*/	
		~PowerUp();
	
		/**
		*	@brief 	Implementacion del metodo de Comestible
		*/
		void afectar_personaje(Personaje& personaje);
	
		/**
		*	@brief 	Implementacion del metodo de Comestible
		*/
		Comestible::Enum_Comestible get_tipo();
		
};

#endif /*__POWER_UP_H__*/
