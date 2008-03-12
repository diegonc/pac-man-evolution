#ifndef __MEMORYREADER_H__
#define __MEMORYREADER_H__

#include "BufferReader.h"

class MemoryReader : public BufferReader
{
	private:
		char* data;
		unsigned int size;
		unsigned int index;

	public:
		/** @brief Construye un lector de un bloque de memoria.
		 *
		 *  @param d Direccion del inicio del bloque.
		 *  @param n Tamano del bloque.
		 */
		MemoryReader( char* d, unsigned int n );

		void recibir( char*d, unsigned int n );
};

#endif /* __MEMORYREADER_H__ */
