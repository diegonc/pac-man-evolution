#ifndef __FRUTITA_H__
#define __FRUTITA_H__

/**
*	@brief	Clase que representa a un comestible del tipo frutita
*/

//TODO cambiar el puntaje para que vaya incrementandoce hasta un tome maximo
//etcs

#include <server/Comestible.h>

class Frutita : public Comestible{
	public:
		
		/**
		*	@brief	Constructor de la clase
		*
		*	@param	p Posicion donde va a estar ubicado el comestible
		*/
		Frutita(Posicion &p):Comestible(10, p){}
		
		/**
		*	@brief	Destructor de la clase
		*/
		~Frutita(){}
		
		/**
		*	@brief Implementacion del metodo afectar_personaje del Comestible
		*
		*	@param	personaje	personaje al cual debe afectar
		*/
		void afectar_personaje(Personaje& personaje){}
			
		/**
		*	@brief Implementacion del metodo get_tipo() de comestibles
		*
		*	@return Tipo de comestible, definido en Comestible
		*/
		Enum_Comestible get_tipo(){return Comestible::frutita;}
};

#endif /*__FRUTITA_H__*/
