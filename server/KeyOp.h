#ifndef __KEYOP_H__
#define __KEYOP_H__

#include "Operacion.h"

class KeyOp : public Operacion
{
	private:
		/* Id de cliente que presiona la tecla. */
		int id;

		/* Tecla presionada
		 *
		 * Por ahora un entero:
		 *    0: Flecha arriba
		 *    1: Flecha abajo
		 *    2: Flecha izquierda
		 *    3: Flecha derecha
		 *
		 * Dada una direccion inicial, segun han sido definidas en Mapa.h, la
		 * direccion resultante se calcula:
		 *         DF = ( DI + Flecha ) % 4
		 */
		int flecha;
	
	public:
		KeyOp( int id, int flecha ) : id( id ), flecha( flecha ) {}
		
		void ejecutar();
};

#endif /* __KEYOP_H__ */
