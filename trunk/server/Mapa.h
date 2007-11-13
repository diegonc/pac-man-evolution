#ifndef __MAPA_H__
#define __MAPA_H__

#include "Jugador.h"
#include "../common/smart_pointer.h"

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

		/** @brief Obtiene un jugador.
		 *
		 *  @param id Identificador del jugador a obtener.
		 *  @return Se devuelve un smart pointer con el jugador.
		 */
		virtual S_ptr<Jugador> get_jugador( int id ) = 0;
			
		/** @brief Obtiene un jugador en una cierta posicion del mapa
		 *
		 *  @param  Cooerdenadas de la posicion en el mapa
		 *  @return Se devuelve un smart pointer con el jugador.
		 */	
		virtual S_ptr<Jugador> get_jugador(int pos_x, int pos_y) = 0;
};

#endif /* __MAPA_H__ */
