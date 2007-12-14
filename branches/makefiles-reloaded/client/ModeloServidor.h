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
		*	@brief	Implementacion del metodo para el thread
		*/
		void run();
   
   		void quitar_jugador(unsigned int id);
};


#endif /*__MODELO_H__*/
