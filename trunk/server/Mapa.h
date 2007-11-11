#ifndef __MAPA_H__
#define __MAPA_H__

#include "Personaje.h"

/** @brief Interfaz de acceso al mapa.
 *
 *  La dispocision de pasillos, conjunto de personajes y los objetos con los
 *  que interactuan conforman un mapa.
 *  La interfaz Mapa se define para permitir el acceso a estor elementos. 
 */
class Mapa
{
	public:
		virtual ~Mapa() {}

		/** @brief Mueve un personaje.
		 *
		 *  @param id  Identificador numerico del personaje.
		 *  @param dir Direccion en la que se mueve el personaje.
		 */
		virtual void mover( int id, Direccion dir ) = 0;

		/** @brief Obtiene un personaje.
		 *
		 *  @param id Identificador del personaje a obtener.
		 *  @return Se devuelve una referencia al personaje.
		 */
		virtual Personaje& get_personaje( int id ) = 0;
			
		/** @brief Obtiene un personaje en una cierta posicion del mapa
		 *
		 *  @param  Cooerdenadas de la posicion en el mapa
		 *  @return Se devuelve una referencia al personaje.
		 */	
		virtual Personaje& get_personaje(int pos_x, int pos_x) = 0;
};

#endif /* __MAPA_H__ */
