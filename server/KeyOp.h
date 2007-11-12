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

		/** @brief Tecla presionada
		 *
		 * Por ahora un entero:
		 *    0: Flecha arriba
		 *    1: Flecha abajo
		 *    2: Flecha izquierda
		 *    3: Flecha derecha
		 */
		int flecha;
	
	public:
		KeyOp( int id, int flecha ) : id( id ), flecha( flecha ) {}
		
		/** @brief Implementa los efectos de la operacion. */
		void ejecutar();
};

#endif /* __KEYOP_H__ */
