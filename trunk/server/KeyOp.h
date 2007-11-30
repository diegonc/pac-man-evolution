#ifndef __KEYOP_H__
#define __KEYOP_H__

#include "Operacion.h"

/** @brief Operacion para mover jugadores.
 *
 */
class KeyOp : public Operacion
{
	private:
		/** @brief Id de cliente que presiona la tecla. */
		int id;
	
		static const int arriba;
		static const int abajo;
		static const int derecha;
		static const int izquierda;

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
		KeyOp( int id, int flecha ) : id( id ), flecha( flecha ) {}
		
		/** @brief Implementa los efectos de la operacion. */
		
		void ejecutar(ModeloServidor &modelo);
};

#endif /* __KEYOP_H__ */
