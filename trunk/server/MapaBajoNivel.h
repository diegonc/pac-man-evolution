#ifndef __MAPA_H__
#define __MAPA_H__

#include "Jugador.h"
#include "Comestible.h"
#include "EstructuralUnitario.h"
#include "Posicion.h"
#include <list>
#include "Objeto.h"

/** @brief Interfaz de acceso al mapa.
 *
 *  La dispocision de pasillos, conjunto de personajes y los objetos con los
 *  que interactuan conforman un mapa.
 *  La interfaz MapaBajoNivel se define para permitir el acceso a estor elementos. 
 */
class MapaBajoNivel
{
	public:
		
		/**
		 * Como vamos a mapear el grafo que tiene cantidades enteras de lados y
		 * hacer la conversion entre (x,y) a lugar en el grafo, lo pongo asi,
		 * de ultima se cambia el typedef.
		 */
		typedef unsigned int Tipo_Dimensiones;

		typedef double Tipo_Coordenada;	
	
		virtual ~MapaBajoNivel() {}

		/** @brief Obtiene el ancho del mapa.
		 */
		virtual Tipo_Dimensiones get_ancho() = 0;

		/** @brief Obtiene el alto del mapa.
		 */
		virtual Tipo_Dimensiones get_alto() = 0;

		/** @brief Mueve un personaje.
		 *
		 *  @param id  Identificador numerico del personaje.
		 *  @param dir Direccion en la que se mueve el personaje.
		 */
		virtual void mover( Jugador& jugador, Tipo_Coordenada distancia ) = 0;
		
		virtual void agregar_estructural(S_ptr<EstructuralUnitario> e)=0;
			
		virtual S_ptr<EstructuralUnitario> get_estructural(Posicion &p)=0;
			
		virtual std::list<S_ptr<EstructuralUnitario> > get_estructurales()=0;	
		
		virtual std::list<S_ptr<Comestible> > get_comestibles()=0;
		//virtual std::list<S_ptr<Objeto> > get_comestibles()=0;
		
};

#endif /* __MAPA_H__ */