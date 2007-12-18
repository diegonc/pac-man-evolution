#ifndef __QUESITO_H__
#define __QUESITO_H__

/**
*	@brief	Esta clase es un comestible. Reprensenta las pastillas que come el
			pacman
*/

#include <server/Comestible.h>

#define PUNTOS_QUESO	1

class Quesito : public Comestible{
	public:
		/**
		*	@brief	Constructor
		*
		*	@param p Posicion del queso
		*/	
		Quesito(Posicion &p):Comestible(PUNTOS_QUESO, p){}
		
		/**
		*	@brief 	Destructor
		*/	
		~Quesito(){}
		
		/**
		*	@brief 	Implementacion del metodo de Comestible
		*/
		void afectar_personaje(Personaje& personaje){}
		
		/**
		*	@brief 	Implementacion del metodo de Comestible
		*/			
		Enum_Comestible get_tipo(){return Comestible::quesito;}
};

#endif /*__QUESITO_H__*/
