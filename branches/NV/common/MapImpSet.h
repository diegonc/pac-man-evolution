#ifndef __MAPAIMPMSET_H__
#define __MAPAIMPMSET_H__

/** @brief 	Implementa una interfaz de mapa utilizando un set como contenedor
 *			de los estructurales
 *
 */

#include "../common/MapaBajoNivel.h"
#include "../common/Jugador.h"
#include "../common/Posicion.h"
#include "ComparadorPosicion.h"
#include "../common/Comestible.h"
#include "../common/observable.h"
#include "../common/NovedadComestible.h"
#include "ComestibleFactory.h"

#include <map>
#include <list>

typedef unsigned int Tipo_Dimensiones;

class MapaImpSet : public MapaBajoNivel{

	private:

		Tipo_Dimensiones ancho;
		Tipo_Dimensiones alto;
	
		/**
		*	@brief 	Este metodo verifica si el jugador, mediante su personaje,
		*			toca alguna pared o borde del mapa.
		*			Se usa para limitar el movimiento
		*
		*	@param	jugador Jugador sobre el cual se desea chequear
		*	@param	pnueva	Posicion a donde va a ir el jugador
		*/
		bool tocando(Jugador &jugador, EstructuralUnitario * donde_esta, Posicion &pnueva);
			
		std::map< unsigned int ,EstructuralUnitario * > estructurales;
		//std::map< unsigned int ,Tipo_Comestible> comestibles;		
		

		unsigned int make_key(Posicion &p);
		
		Posicion unmake_key(unsigned int key);
		
		
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
		void agregar_estructural(EstructuralUnitario * e);

		/**
		*	@brief	Implementacion del metodo de mapa
		*
		*	@param 	p Posicion donde se busca el estructural
		*
		*	@return Smart pointer con el estructural
		*/
		EstructuralUnitario * get_estructural(Posicion &p);

		/**
		*	@brief	Implementacion del metodo de mapa
		*
		*	@return lista con los estructurales
		*/
		std::list<EstructuralUnitario * > get_estructurales();

		/**
		*	@brief	Implementacion del metodo de mapa
		*
		*	@param 	lista con los comestibles
		*/
		std::list<Comestible * > get_comestibles();
	
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

		/**
		*	@brief	Permite actualizar sacando un comestible
      	*
      	*  @param   vertice Vertice de donde sacarle el comestible
		*/
		void refresh(unsigned int vertice);
		
  		/**
		*	@brief	Permite actualizar agregando un comestible
      	*
      	*  	@param   vertice Vertice de donde sacarle el comestible
      	*
      	*  	@param   tipo_comestible Comestible que se desea agregar
		*/
		void refresh(unsigned int vertice, Comestible::Enum_Comestible tipo_comestible);
   
      /**
		*	@brief	Metodo para quitar un comestible de la lista propia
		*	
		*	@param	comestible Comestible que se quiere quitar
		*
		void quitar_comestible(Tipo_Comestible comestible);*/		
   
      /**
      *  @brief   Implementacion de la interfaz.
      *
      */
		EstructuralUnitario * get_salida_pacman();
      
      /**
      *  @brief   Implementacion de la interfaz.
      *
      */		
		std::list<EstructuralUnitario *> get_casa_fantasma();
      
      /**
      *  @brief   Corrige la posicion pasada por parametro, es decir, se se pasa de los bordes
      *           del mapa, da la vuelta y la pone donde iria para que caiga en este
      *  
      */
      void corregir_posicion(Posicion &p);
		
};

#endif /* __MAPAIMPMSET_H__ */
