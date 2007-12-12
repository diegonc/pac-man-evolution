#ifndef __MODELO_H__
#define __MODELO_H__

#include "../common/thread.h"
#include "../common/smart_pointer.h"
#include "MundoBasicImp.h"
#include <string>
#include <list>
#include "Jugador.h"
#include "../common/observador.h"
//#include "../common/observable.h"

/** @brief Esta clase define el modelo.
 *		   Hereda de thread, ya que se debe actualizar automaticamente todo
 *		   el tiempo la posicion de los jugadores.
 */

class ModeloServidor : public Thread , public Observador, public Observable{
	typedef S_ptr<Jugador> Tipo_Jugador;
	
	private:
		S_ptr<MundoBajoNivel> mundo;
	
		std::list<Tipo_Jugador> jugadores;
		
		ModeloServidor(ModeloServidor &m);
		
		bool parar;
		bool termino;
	
		int cant_min_jugadores;
		int cant_max_jugadores;
	
		void cargar_modelo(); //PROVISORIA PARA CARGAR; DESPUES SACAR
	
		void preparar_partida();
					
		void revisar_colisiones(S_ptr<Jugador>& j);	
	
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
		void agregar_jugador(Tipo_Jugador jugador);
			
		/**
		*	@brief	Implementacion del metodo para el thread
		*/
		void run();
	
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
		S_ptr<Jugador> get_jugador(int id);
	
		/**
		*	@brief	Permite obtener una lista con todos los jugadores que tiene
		*			el modelo
		*
		*	@return	Lista con los jugadores
		*/
		const std::list<S_ptr<Jugador> >& get_jugadores();
	
		/**
		*	@brief Implementacion del metodo actualizar de la clase observador
		*/
		virtual void actualizar(Observable * observable, void * param);
	
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
};


#endif /*__MODELO_H__*/
