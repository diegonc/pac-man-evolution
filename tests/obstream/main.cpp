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

int main()
{
	test_1();
	test_2();
	return 0;
}

