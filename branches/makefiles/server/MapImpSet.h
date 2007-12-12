#ifndef __MAPAIMPMSET_H__
#define __MAPAIMPMSET_H__

/** @brief 	Implementa una interfaz de mapa utilizando un set como contenedor
 *			de los estructurales
 *
 */

#include "MapaBajoNivel.h"
#include "Jugador.h"
#include "Posicion.h"
#include "ComparadorPosicion.h"
#include "Comestible.h"
#include <set>

typedef unsigned int Tipo_Dimensiones;
typedef S_ptr<EstructuralUnitario> Tipo_Estructural;

class MapaImpSet : public MapaBajoNivel{

	private:

		Tipo_Dimensiones ancho;
		Tipo_Dimensiones alto;

		Tipo_Estructural estructural;

		/**
		*	@brief 	Este metodo verifica si el jugador, mediante su personaje,
		*			toca alguna pared o borde del mapa.
		*			Se usa para limitar el movimiento
		*
		*	@param	jugador Jugador sobre el cual se desea chequear
		*	@param	pnueva	Posicion a donde va a ir el jugador
		*/
		bool tocando(Jugador &jugador, S_ptr<EstructuralUnitario> donde_esta, Posicion &pnueva);
		

	public:
		/**
		*	@brief	Inner class que sirve para comparar el contenido del set.
		*			Sirve para el ordenamiento del mismo
		*/
		class CompSptrEstructuralPosicion{
			public:
				bool operator()(const Tipo_Estructural &e1, const Tipo_Estructural &e2){
					Tipo_Estructural v1 = e1;
					Tipo_Estructural v2 = e2;

					Posicion pos1 = v1->get_posicion();
					Posicion pos2 = v2->get_posicion();
	
					if( (int)pos1.get_x() < (int)pos2.get_x() )
						return true;
					else
						if((int)pos1.get_y() < (int)pos2.get_y())
							return true;
						else
							return false;
					}
		};
	private:
		std::set<Tipo_Estructural,CompSptrEstructuralPosicion> estructurales;
		std::list<S_ptr<Comestible> > comestibles;
		
		/**
		*	@brief	Metodo para quitar un comestible de la lista propia
		*	
		*	@param	comestible Comestible que se quiere quitar
		*/
		void quitar_comestible(S_ptr<Comestible> comestible);

	public:
		/**
		*	@brief Constructor
		*
		*	@param	ancho	Ancho del mapa (es respecto al eje x)
		*	@param 	alto    Alto del mapa (es respecto al eje y)
		*/
		MapaImpSet(const Tipo_Dimensiones ancho, const Tipo_Dimensiones alto);
		
		/**
		*	@brief Destructor de la clase
		*/
		~MapaImpSet();
		
		/**
		*	@brief	Permite mover un jugador en la direccion que este posee 
		*			una distancia determinada
		*
		*	@param	jugador Jugador que se desea mover
		*	@param 	distancia Distancia que se deseea over al jugador
		*/
		void mover( Jugador& jugador, Tipo_Coordenada distancia );

		/**
		*	@brief	Implementacion del metodo de mapa
		*
		*	@param 	e Estructural a agregar
		*/
		void agregar_estructural(S_ptr<EstructuralUnitario> e);

		/**
		*	@brief	Implementacion del metodo de mapa
		*
		*	@param 	p Posicion donde se busca el estructural
		*
		*	@return Smart pointer con el estructural
		*/
		S_ptr<EstructuralUnitario> get_estructural(Posicion &p);

		/**
		*	@brief	Implementacion del metodo de mapa
		*
		*	@return lista con los estructurales
		*/
		std::list<S_ptr<EstructuralUnitario> > get_estructurales();

		/**
		*	@brief	Implementacion del metodo de mapa
		*
		*	@param 	lista con los comestibles
		*/
		std::list<S_ptr<Comestible> > get_comestibles();
	
		/**
		*	@brief	Devuelve el ancho del mapa
		*
		*	@return el ancho del mapa
		*/
		Tipo_Dimensiones get_ancho();

		/**
		*	@brief	Devuelve el alto del mapa
		*
		*	@return el alto del mapa
		*/
		Tipo_Dimensiones get_alto();

		void refresh(std::list< S_ptr<Comestible> >& comestibles_totales);
};

#endif /* __MAPAIMPMSET_H__ */
