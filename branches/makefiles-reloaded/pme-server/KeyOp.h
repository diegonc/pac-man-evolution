#ifndef __KEYOP_H__
#define __KEYOP_H__

#include <server/Operacion.h>

/** @brief Operacion para mover jugadores.
 *
 */
class KeyOp : public Operacion
{
	private:
		/** @brief Id de cliente que presiona la tecla. */
		unsigned int id;

		/** @brief Tecla presionada
		 *
		 * Por ahora un entero:
		 *    0: Flecha arriba
		 *    2: Flecha abajo
		 *    1: Flecha derecha
		 *    3: Flecha izquierda
		 */
		int flecha;
	
	public:
		static const int arriba;
		static const int abajo;
		static const int derecha;
		static const int izquierda;

		/**
		*	@brief Constructor de la clase
		*/
		KeyOp( unsigned int id, int flecha );// : id( id ), flecha( flecha ) {}

		KeyOp( unsigned int flecha ):flecha(flecha){}
		
		/** 
		*	@brief Implementa los efectos de la operacion. 
		*/		
		void ejecutar(ModeloCommon &modelo);

		void set_id(unsigned int identifJugador);

		int get_flecha(){ return flecha; }
};

#endif /* __KEYOP_H__ */
