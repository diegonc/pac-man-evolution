#include "BitStream.h"
#include <cassert>

BitStream::BitStream( Socket& s ) : sock( s )
{
}

int BitStream::read( int n )
{
	assert( n <= 8*sizeof( int ) );

	unsigned int mask_table[8] = {
		1,   // 00000001b
		3,   // 00000011b
		7,   // 00000111b
		15,  // 00001111b
		31,  // 00011111b
		63,  // 00111111b
		127, // 01111111b
		255  // 11111111b
	};
	char test = 44;
	char* buffer = &test;
	int size = 1;
	int index = 0;
	int bindex = 8;

	int bavail = bindex + 8 * ( size - index - 1 );
	
	if( bavail < n ) {
		// leer: n-bavail bits
	}

	int r = 0;

	while( n > bindex ){
		r <<= bindex;
		r |= ( mask_table[bindex-1] & buffer[index] );
		bindex = 8;
		index++;
		n -= bindex;
	}
	if( n > 0 ) {
		unsigned int mask = ( mask_table[n-1] << ( bindex - n ) );
		r <<= n;
		r |= ( ( buffer[index] & mask ) >> ( bindex-n ) );
		bindex -= n;
	}
	return r;
}
