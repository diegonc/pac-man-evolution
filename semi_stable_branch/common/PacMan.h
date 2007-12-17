#ifndef __PACMAN_H__
#define __PACMAN_H__

/**
*	@brief	Implementacion de personaje. Reprensenta al pacman
*/

#include "Personaje.h"

#include "Jugador.h"
#include "Comestible.h"
#include "thread.h"

class PacMan : public Personaje{
	private:
		class RemovedorPowerUp;

		bool power_up_activado;
		double velocidad;
		S_ptr<RemovedorPowerUp> removedor;
	
	
		static const double VELOCIDAD_PACMAN_NORMAL;
		static const double VELOCIDAD_PACMAN_PW;
		static const double RADIO_PACMAN;
	
	public:
		/**
		*	@brief	Constructor
		*
		*	@param	jugador Jugador al cual pertenece
		*/
		PacMan(Jugador *jugador);
	
		/**
		*	@brief	Implementacion del metodo comer de personaje
		*/
		bool comer(Comestible& comestible);
	
		/**
		*	@brief	Implementacion del metodo comer de personaje
		*/
		void colision(Jugador * jugador);
	
		/**
		*	@brief	Permite activar o desactivar el power up
		*
		*	@param	activado true si esta activado, false en caso contrario
		*/
		void set_power_up(bool activado);
	
		/**
		*	@brief	Permite saber si tiene o no el power up activado
		*
		*	@return true en caso de que este activado, false en caso contrario
		*/
		bool tiene_power_up();
	
		/**
		*	@brief	Implementacion del metodo comer de personaje
		*/
		Personaje::Enum_Personaje get_tipo();
	
		/**
		*	@brief	Implementacion del metodo comer de personaje
		*/
		double get_velocidad();
};

#endif /*__PACMAN_H__*/
