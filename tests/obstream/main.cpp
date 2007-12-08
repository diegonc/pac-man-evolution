#include "../../server/OutputBitStream.h"
#include <iostream>

void test_1()
{
	OutputBitStream obs;
	obs.append( 8, 56 );
	const unsigned char* raw = obs.get_data();
	if( obs.get_size() != 1 )
		std::cout << "ERROR: tamano " << obs.get_size() << " (esperado: " << 1 << "\n";
	else if( raw[0] != 56 ) 
		std::cout << "ERROR: byte 1 es " << (int)raw[0] << " (esperado: 56\n";
}

void test_2()
{
	OutputBitStream obs;
	obs.append( 2, 0 );
	obs.append( 3, 0 );
	obs.skip();
	const unsigned char* raw = obs.get_data();
	if( obs.get_size() != 1 )
		std::cout << "ERROR: tamano " << obs.get_size() << " (esperado: " << 1 << "\n";
	else if( raw[0] != 0 ) 
		std::cout << "ERROR: byte 1 es " << (int)raw[0] << " (esperado: 0\n";
}

void test_3()
{
	OutputBitStream obs;
	obs.append( 2, 0 );
	obs.append( 3, 0 );
	obs.append( 3, 1 );
	obs.append( 8, 3 );
	const unsigned char* raw = obs.get_data();
	if( obs.get_size() != 2 )
		std::cout << "ERROR: tamano " << obs.get_size() << " (esperado: 2 )\n";
	else {
		int outs[2] = { 1, 3 };
		for( int i = 0; i < 2; i++ ) {
		       	if( raw[i] != outs[i] ) {
				std::cout << "ERROR: byte " << i << " es ";
				std::cout << (int)raw[i] << " (esperado: " << outs[i] << ")\n";
			}
		}
	}
}


int main()
{
	test_1();
	test_2();
	test_3();
	return 0;
}

