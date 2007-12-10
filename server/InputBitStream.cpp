#include "InputBitStream.h"
#include <cassert>
#include <stdexcept>
#include <cstring>

namespace {
	char test[2] = { 44, -92/* 164 */ };

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
}

InputBitStream::InputBitStream( BufferReader& br ) : br( br )
{
	buffer = 0;
	size = 0;
	index = 0;
	bindex = 8;
}

InputBitStream::~InputBitStream()
{
	if( buffer )
		delete[] buffer;
}

void InputBitStream::grow( unsigned int n )
{
	unsigned int bavail = bindex + 8 * ( size - index - 1 );

	if( bavail < n ) {
		unsigned int bits_needed = n - bavail;
		unsigned int bytes_needed = bits_needed / 8;
		if( bits_needed % 8 ) bytes_needed++;
		
		unsigned int current_data_size = size - index;
		char* new_buffer = new char[current_data_size + bytes_needed];

		memcpy( new_buffer, buffer + index, current_data_size );
		if( buffer ) delete[] buffer;
		
		br.recibir( new_buffer + current_data_size, bytes_needed );
		index = 0;
		size = current_data_size + bytes_needed;
		buffer = new_buffer;
	}
}

int InputBitStream::read( unsigned int n )
{
	assert( n <= 8*sizeof( int ) );

	grow( n );

	int r = 0;

	while( n > bindex ){
		r <<= bindex;
		r |= ( mask_table[bindex-1] & buffer[index] );
		index++;
		n -= bindex;
		bindex = 8;
	}
	if( n > 0 ) {
		unsigned int mask = ( mask_table[n-1] << ( bindex - n ) );
		r <<= n;
		r |= ( ( buffer[index] & mask ) >> ( bindex-n ) );
		bindex -= n;
		if( bindex == 0 ) { index++; bindex = 8; }
	}
	return r;
}

void read_string( char* s, unsigned int n )
{
	while( n > 0 ) {
		*s = (char) read( 8 );
		if( *s == 0 ) break;
		n--;
		s++;
	}
}

void InputBitStream::skip()
{
	if( index < size ) {
		if( bindex != 8 ) {
			index++;
			bindex = 8;
		}
	}
}
#if 0
char* InputBitStream::read_block( unsigned int	n, unsigned int& m )
{
	grow( n );

	if( bindex == 8 ) {
		/*
		 * Buenisimo =P, los datos comienzan al principio de un byte.
		 */
		m = ( n % 8 ) ? ( n / 8 + 1 ) : ( n / 8 );
		char* block = new char[m];
		memcpy( block, buffer+index, m );
		index += n / 8;
		bindex -= n % 8;
		return block;
	} else {
		/*
		 * ... horrible. Espero no suceda.
		 */
		throw std::runtime_error( "Implementar read_block desalineado." );
	}
}
#endif
