#ifndef __MAPA_H__
#define __MAPA_H__

#include "Jugador.h"
#include "Comestible.h"

/** @brief Interfaz de acceso al mapa.
 *
 *  La dispocision de pasillos, conjunto de personajes y los objetos con los
 *  que interactuan conforman un mapa.
 *  La interfaz Mapa se define para permitir el acceso a estor elementos. 
 */
class Mapa
{
	typedef double Tipo_Coordenada;	
	
	public:
		virtual ~Mapa() {}

		/** @brief Mueve un personaje.
		 *
		 *  @param id  Identificador numerico del personaje.
		 *  @param dir Direccion en la que se mueve el personaje.
		 */
		virtual void mover( Jugador * jugador, Direccion dir ) = 0;

		/* @brief Obtiene un jugador.
		 *
		 *  @param id Identificador del jugador a obtener.
		 *  @return Se devuelve un smart pointer con el jugador.
		 
		virtual S_ptr<Jugador> get_jugador( int id ) = 0;
			
		* @brief Obtiene un jugador en una cierta posicion del mapa
		 *
		 *  @param  Cooerdenadas de la posicion en el mapa
		 *  @return Se devuelve un smart pointer con el jugador.
		
		virtual S_ptr<Jugador> get_jugador(Tipo_Coordenada pos_x, Tipo_Coordenada pos_y) = 0;
		*/
		
		/** @brief Obtiene un Comestible en una posicion del mapa
		 *
		 *  @param  Cooerdenadas de la posicion en el mapa
		 *  @return Se devuelve un smart pointer con el comestible.
		*/
		virtual S_ptr<Comestible> get_comestible(Tipo_Coordenada pos_x, Tipo_Coordenada pos_y) = 0;
		
		/** @brief Le asigna la posicion inicial al jugador dependiendo si es 
		 *		   Pac-Man o Fantasma
		 *
		 *  @param  Jugador a agregar
		 */
		virtual void establecer_posicion_inicial(Jugador * jugador) = 0;
};

#endif /* __MAPA_H__ */
