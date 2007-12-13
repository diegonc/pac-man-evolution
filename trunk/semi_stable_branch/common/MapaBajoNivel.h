#ifndef __MAPA_H__
#define __MAPA_H__

/** @brief Interfaz de acceso al mapa.
 *
 *  La dispocision de pasillos, conjunto de personajes y los objetos con los
 *  que interactuan conforman un mapa.
 *  La interfaz MapaBajoNivel se define para permitir el acceso a estor elementos. 
 */

#include "Jugador.h"
#include "Comestible.h"
#include "EstructuralUnitario.h"
#include "Posicion.h"
#include <list>
#include "../common/observable.h"

class MapaBajoNivel : public Observable
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

		/** @brief 	La implementacion debe permitir mover el personaje
		 *
		 *  @param id  Identificador numerico del personaje.
		 *  @param dir Direccion en la que se mueve el personaje.
		 */
		virtual void mover( Jugador& jugador, Tipo_Coordenada distancia ) = 0;
		
		/** @brief 	El que implemente este metodo debe permitir 
		 *			agregar un estructural al mapa.
		 *
		 *  @param e Smart_pointer con el estructural agregar
		 */
		virtual void agregar_estructural(S_ptr<EstructuralUnitario> e)=0;
		
		/** @brief 	El que implemente este metodo debe permitir 
		 *			obtener un estructural en la posicion dada. De no existir
		 *			debe devolver un smart_pointer nulo
		 *
		 *  @param e Smart_pointer con el estructural buscado.
		 */
		virtual S_ptr<EstructuralUnitario> get_estructural(Posicion &p)=0;
		
		/**	@brief	Debe devolver una lista con los estructurales que contiene
		*			el mapa.
		*	
		*	@return	Una lista con estructurales
		*/		
		virtual std::list<S_ptr<EstructuralUnitario> > get_estructurales()=0;	
		
		/** @brief	Debe devolver los comestibles que posee el mapa en una
		*			lista
		*
		*	@return Lista con los comestibles
		*/		
		virtual std::list<S_ptr<Comestible> > get_comestibles()=0;

		virtual void refresh( std::list< S_ptr<Comestible> >& comestibles_totales ) = 0;
};

#endif /* __MAPA_H__ */
