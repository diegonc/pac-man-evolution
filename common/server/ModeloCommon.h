#ifndef __MODELO_COMMON_H__
#define __MODELO_COMMON_H__

#include <common/thread.h>
#include <common/smart_pointer.h>
#include <server/MundoBasicImp.h>
#include <string>
#include <map>
#include <server/Jugador.h>
#include <common/bloqueo.h>

/** @brief Esta clase define el modelo.
 *		   Hereda de thread, ya que se debe actualizar automaticamente todo
 *		   el tiempo la posicion de los jugadores.
 */

class ModeloCommon : public Thread, public Observable{
		
	protected:
		S_ptr<MundoBajoNivel> mundo;
	
      	std::map<unsigned int, Jugador*> jugadores;
		
		ModeloCommon(ModeloCommon &m);

		bool termino;
	   
      	Mutex llave;
	
	public:
   	/**
		*	@brief 	Constructor de la clase
		*
		*/
		ModeloCommon();
   	
		/**
		*	@brief 	Destructor de la clase
		*/
		~ModeloCommon();	
	
		/**
		*	@brief 	Agrega un jugador al modelo y le asigna el personaje
		*
		*	@param	jugador Jugador a agregar
		*/
		virtual void agregar_jugador(Jugador * jugador);
			
		/**
		*	@brief	Implementacion del metodo para el thread
		*/
		virtual void run() = 0;
	
		/**
		*	@brief	Devuelve el mundo del modelo
		*
		*	@return Mundo del modelo
		*/
		MundoBajoNivel& get_mundo();
	
		/**
		*	@brief	Permite obtener un jugador a partir del id del mismo
		*
		*	@param	id Id del jugador a buscar.
		*
		*	@return	Smart pointer con el jugador y si no existe un smart pointer
		*			nulo
		*/
		Jugador * get_jugador(unsigned int id);
	
		/**
		*	@brief	Permite obtener una lista con todos los jugadores que tiene
		*			el modelo
		*
		*	@return	Lista con los jugadores
		*/
		const std::list<Jugador *> get_jugadores();
	
		/**
		*	@brief	Permite setearle el mundo
		*
		*	@param mundo Smart pointer cuyo contenido es el mundo
		*/
		void set_mundo(S_ptr<MundoBajoNivel> mundo);
		
		/**
		*	@brief	Permite conocer el estado del juego
		*
		*	@return True si ya termino el juego, es decir se jugaron todos los
		*			niveles o no hay mas jugadores, false en caso contrario
		*
		*/
		bool esta_terminado();

		void set_cargado();
		
      /**
      *  @brief   Permite quitar un jugador
      * 
      *  @param   id Id del jugador a quitar
      */
  		void quitar_jugador(unsigned int id);

      void preparar_partida();

      /**
      *  @brief   Settea la posicion inicial del jugador dependiendo del personaje
      *
      *  @param   jugador Jugador al cual se le settea
      */
      void set_posicion_inicial( Jugador * jugador );
};


#endif /*__MODELO_COMMON_H__*/
