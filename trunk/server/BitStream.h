#ifndef __BITSTREAM_H__
#define __BITSTREAM_H__

#include "../common/socket.h"

class BitStream
{
	private:
		Socket& sock;

	public:
		/** @brief Construye un BitStream para leer desde un Socket.
		 *
		 */
		BitStream( Socket& s );

		/** @brief Lee del stream n bits.
		 *
		 *  Devuelve el valor numerico de los siguientes n bits en el
		 *  stream y los remueve del mismo.
		 *
		 *  Precondiciones:
		 *    - n > 0
		 *    - n <= 8*sizeof(int)
		 *  Postcondiciones:
		 *    - n bits del stream se copian al resultado.
		 *    - se mantienen en el orden de izq a der.
		 *  @param n Numero de bits a leer.
		 *  @return Representacion numerica.
		 */
		int read( int n );

};

#endif /* __BITSTREAM_H__ */
