#ifndef __FANTASMA_H__
#define __FANTASMA_H__

/**
*	@brief Implementacion de personaje. 
*/

#include "Personaje.h"

class Fantasma : public Personaje{
	public:
		
		/**
		*	@brief Constructor de la clase.
		*
		*	@param jugador Jugador al cual pertenece
		*/
		Fantasma(Jugador *jugador);	
	
		/**
		*	@brief 	Implementa el metodo comer de personaje. Realiza las 
		*			operaciones necesarios sobre el comestible y el jugador
		*			al cual pertenece
		*
		*	@param 	comestible Comestible que come
		*/
		bool comer(Comestible& comestible);
	
		/**
		*	@brief	Implementa el metodo de colision ente el personaje y el del
		*			jugador pasado por parametro. 
		*
		*	@para 	jugador	Jugador con cuyo personaje colisiono
		*/
		void colision(Jugador& jugador);
		
		/**
		*	@brief	Permite obtener el tipo de personaje
		*
		*	@return Enum_Personaje definido en la clase Personaje
		*/
		Enum_Personaje get_tipo();
	
	
		double get_velocidad();
};

#endif /*__FANTASMA_H__*/
