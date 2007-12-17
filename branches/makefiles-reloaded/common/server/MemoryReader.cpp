#include <server/MemoryReader.h>
#include <cstring>
#include <stdexcept>

MemoryReader::MemoryReader( char* d, unsigned int n )
{
	data = d;
	index = 0;
	size = n;
}

void MemoryReader::recibir( char* d, unsigned int n )
{
	unsigned int avail = size - index;

	if( n <= avail ) {
		memcpy( d, data + index, n );
		index += n;
	} else
		throw std::runtime_error( "MemoryReader::recibir: "
				"datos insuficientes." );
}
