#ifndef __INPUTBITSTREAM_H__
#define __INPUTBITSTREAM_H__

#include "BufferReader.h"

class InputBitStream
{
	private:
		/** @brief Origen de datos.
		 */
		BufferReader& br;

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

	public:
		/** @brief Construye un InputBitStream para leer desde un Socket.
		 *
		 */
		InputBitStream( BufferReader& s );

		~InputBitStream();

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

		/** @brief Descarta los bits restantes del byte actual.
		 *
		 *  Descarta los bits restantes del byte actual, dejando el
		 *  puntero al comienzo del siguiente byte.
		 */
		void skip();

		/** @brief Obtiene bloque de bytes.
		 *
		 *  Obtiene el bloque de bytes mas pequeno que contiene los
		 *  siguientes n bits del stream.
		 *  Los n bits se retiran del stream.
		 *
		 *  Precondicion:
		 *      - el valor de retorno es un arreglo de char y debe ser
		 *      liberado con delete[].
		 *
		 *  @param n Numero de bits extraidos.
		 *  @param m Numero de bytes del bloque.
		 *  @return Bloque que contiene los bits.
		 */
		char* read_block( unsigned int n, unsigned int& m );


		/** @brief Rellena el buffer.
		 *
		 *  Rellena el buffer con suficientes datos para extraer los n
		 *  bits solicitados.
		 *  Los datos ya extraidos y que permanecen en el buffer son
		 *  descartados.
		 */
		void grow( unsigned int n );
};

#endif /* __INPUTBITSTREAM_H__ */
