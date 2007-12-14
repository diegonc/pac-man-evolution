#ifndef __MODELO_H__
#define __MODELO_H__

#include "../common/ModeloCommon.h"

/** @brief Esta clase define el modelo.
 *		   Hereda de thread, ya que se debe actualizar automaticamente todo
 *		   el tiempo la posicion de los jugadores.
 */

class ModeloServidor : public ModeloCommon {

	typedef S_ptr<Jugador> Tipo_Jugador;
	
	private:
	
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
};


#endif /*__MODELO_H__*/
