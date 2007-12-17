#ifndef __MODELO_H__
#define __MODELO_H__

#include "../common/ModeloCommon.h"
#include "../common/observador.h"
#include "reloj.h"
#include "../common/PacMan.h"
#include "../common/Fantasma.h"
#include <cassert>

/** @brief Esta clase define el modelo.
 *		   Hereda de thread, ya que se debe actualizar automaticamente todo
 *		   el tiempo la posicion de los jugadores.
 */

class ModeloServidor : public ModeloCommon, public Observador {

	//typedef S_ptr<Jugador> Tipo_Jugador;
	
	private:
  		bool parar;	
   
		void preparar_partida();
					
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
};


#endif /*__MODELO_H__*/
