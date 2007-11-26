#ifndef __MAPA_H__
#define __MAPA_H__

#include "Jugador.h"
#include "Comestible.h"
#include "Estructural.h"
#include "Posicion.h"

/** @brief Interfaz de acceso al mapa.
 *
 *  La dispocision de pasillos, conjunto de personajes y los objetos con los
 *  que interactuan conforman un mapa.
 *  La interfaz Mapa se define para permitir el acceso a estor elementos. 
 */
class Mapa
{
	protected:
		typedef double Tipo_Coordenada;	
	
	public:
		virtual ~Mapa() {}

		/** @brief Mueve un personaje.
		 *
		 *  @param id  Identificador numerico del personaje.
		 *  @param dir Direccion en la que se mueve el personaje.
		 */
		virtual void mover( Jugador& jugador, Direccion &dir, Tipo_Coordenada distancia ) = 0;
		
		virtual void agregar_estructural(S_ptr<Estructural>, Posicion &p)=0;
			
		virtual S_ptr<Estructural> get_estructural(Posicion &p)=0;
			
	
};

#endif /* __MAPA_H__ */
