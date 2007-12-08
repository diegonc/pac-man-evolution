#include "OutputBitStream.h"
#include <string>

OutputBitStream::OutputBitStream(){
	this->buffer = new unsigned char[_DEFAULT_SIZE];
	this->buffer[0] = 0;
	this->bit_index = 0;
	this->buffer_size = _DEFAULT_SIZE;
	this->_return = 0;//TODO SACAR!!!
	
}
OutputBitStream::~OutputBitStream(){
	delete[] this->buffer;
	if(_return != 0)
		delete[] _return;
}
void OutputBitStream::append( const unsigned int n, int val, bool grow ){
	
	//obtengo el la cantidad de bits disponibles
	unsigned int bavail = (buffer_size * 8 - bit_index );
	//si la cantidad es mayor o puede crecer
	if(  bavail >= n || grow ){
		//si la cantidad era menor, lo hago crecer
		if(bavail < n)
			this->grow(n - bavail);
		
		//lo desplazo n bits para meter los nuevos
		shift_left(n);
				
		unsigned int index = 0;
		while( index < n){
			if( val  & (1 << index) ) //si hay 1
				(*( buffer + index / 8 )) |= (1 << index); //guardo 1
			index++;
		}
		bit_index += n ;
	}
	
}

void OutputBitStream::skip(){
	shift_left(buffer_size * 8 - bit_index);
	bit_index = buffer_size * 8;
}

void OutputBitStream::grow( unsigned int n ){
	unsigned int bsize = buffer_size * 8 + n; 
	
	if(n > 0){
		//creo el nuevo buffer
		unsigned int new_buffer_size = ( bsize % 8==0 ) ? bsize/8 : ( bsize/8 + 1);
		unsigned char * new_buffer = new unsigned char [ new_buffer_size ];
		//los copio
		memcpy(new_buffer, buffer, new_buffer_size - buffer_size);
		//borro el viejo
		delete[] this->buffer;
		//setteo los tamaños
		buffer_size = new_buffer_size;
		//setteo el nuevo buffer
		this->buffer = new_buffer;
		
			
	}
}
#include <iostream>
const unsigned char* OutputBitStream::get_data(){
	//TODO: CAMBIARLO COMO LO QUIERE ÑETO
	
	
	int d_index = 0;
	if(_return != 0)
		delete[] _return;
	
	_return = new unsigned char[buffer_size];
	//skip();
	for(int o_index = buffer_size - 1 ; o_index >= 0; o_index--){
		_return[d_index] = buffer[o_index];
		d_index++;
	}
	
	return _return;
	
}
void OutputBitStream::shift_left(const unsigned int n_bits){
	
	unsigned int aux;
	for(int index = bit_index - 1 ; index >= 0; index--){
		aux = (index + n_bits) / 8 ;
		if(aux <= buffer_size ){
			if(	*buffer &  (1 << index % 8) ) //era 1
				(*( buffer + aux )) |= (  1 << (index + n_bits) % 8) ;
			else
				(*( buffer + aux )) &= ~( 1 << (index + n_bits) % 8) ;
			
			(*( buffer + index / 8 )) &= ~( 1 << (index) % 8) ;
		}
	}
}
unsigned int OutputBitStream::get_size(){
	return buffer_size;
}

unsigned int OutputBitStream::bits_needed(unsigned int num){
	
	unsigned int count = 0;
	
	while( num >= 2 ){
		count++;
		num /= 2;
	}
	count ++;
		
	return count;	
	
}
