#ifndef __MODELO_H__
#define __MODELO_H__

#include <server/ModeloCommon.h>
#include <common/observador.h>
#include "reloj.h"
#include <server/PacMan.h>
#include <server/Fantasma.h>
#include <common/evento.h>
#include <cassert>

/** @brief Esta clase define el modelo.
 *		   Hereda de thread, ya que se debe actualizar automaticamente todo
 *		   el tiempo la posicion de los jugadores.
 */

class ModeloServidor : public ModeloCommon, public Observador {
	
	private:

  		bool nivel_terminado; //Determina si el nivel actual termino o no

      bool pausado; //Determina si el modelo esta pausado en el nivel actual o no

      Evento* evento_despausar; //Evento que controla el despausar
					
		void revisar_colisiones(Jugador * j, std::list<Jugador *>& lista_jugadores);	
	
		/**
		*	@brief 	Constructor de la clase
		*
		*/
		ModeloServidor();
	
		static S_ptr<ModeloServidor> instancia;
	public:
				
		static S_ptr<ModeloServidor> get_instancia();
	
		/**
		*	@brief 	Destructor de la clase
		*/
		~ModeloServidor();	
	
		/**
		*	@brief 	Agrega un jugador al modelo y le asigna el personaje
		*
		*	@param	jugador Jugador a agregar
		*/
		void agregar_jugador(Jugador * jugador);
			
		/**
		*	@brief	Implementacion del metodo para el thread
		*/
		void run();

     	/**
		*	@brief Implementacion del metodo actualizar de la clase observador
		*/
		virtual void actualizar(Observable * observable, void * param);

      /**
      *  @brief Reinicia la partida reasignando las posiciones a los jugadores. Si
      *         no existe un pacman, se lo settea a otro jugador
      */
      void reiniciar_partida();

      /**
      *  @brief Pausa el modelo en el nivel actual si no estaba pausado.
      */
      void pausar();

      /**
      *  @brief Si el modelo estaba pausado, lo despausa, sino no hace nada.
      */
      void despausar();

      /**
      *  @return Devuelve si esta pausado o no el modelo.
      */
      bool esta_pausado();

};


#endif /*__MODELO_H__*/
