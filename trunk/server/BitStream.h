#ifndef __BITSTREAM_H__
#define __BITSTREAM_H__

#include "../common/socket.h"

class BitStream
{
	private:
		Socket& sock;

		/** @brief Almacenamiento para mantener los datos a procesar.
		 */
		char* buffer;

		/** @brief Tamano del buffer.
		 */
		unsigned int size;

		/** @brief Puntero al byte actual.
		 *
		 *  Se utiliza para acceder al buffer. Apunta al byte del cual
		 *  se extraeran los datos.
		 */
		unsigned int index;
		
		/** @brief Puntero al bit actual.
		 *
		 *  Se utiliza para acceder al buffer. Es un indicador de la
		 *  cantidad de bits disponibles en el stream que corresponden
		 *  al byte actual.
		 */
		unsigned int bindex;

		/** @brief Rellena el buffer.
		 *
		 *  Rellena el buffer con suficientes datos para extraer los n
		 *  bits solicitados.
		 *  Los datos ya extraidos y que permanecen en el buffer son
		 *  descartados.
		 */
		void grow( unsigned int n );
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
		 *    - n <= 8*sizeof(int)
		 *  Postcondiciones:
		 *    - n bits del stream se copian al resultado.
		 *    - se mantienen en el orden de izq a der.
		 *  @param n Numero de bits a leer.
		 *  @return Representacion numerica.
		 */
		int read( unsigned int n );

};

#endif /* __BITSTREAM_H__ */
