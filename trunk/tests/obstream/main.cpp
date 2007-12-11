#include "../../server/OutputBitStream.h"
#include <iostream>

void test_1()
{
	std::cout << "Corriendo test_1().\n";
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
	std::cout << "Corriendo test_2().\n";
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
	std::cout << "Corriendo test_3().\n";
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

void test_4()
{
	std::cout << "Corriendo test_4().\n";

	OutputBitStream obs;
	obs.append( 2, 0 );
	obs.append( 3, 0 );
	obs.append( 3, 1 );
	obs.append( 8, 3 );
	obs.append( 3, 4 );
	obs.append( 4, 12 );
	obs.append( 1, 1 );
	const unsigned char* raw = obs.get_data();
	if( obs.get_size() != 3 )
		std::cout << "ERROR: tamano " << obs.get_size() << " (esperado: 3 )\n";
	else {
		int outs[3] = { 0x01, 0x03, 0x99 };
		for( int i = 0; i < 3; i++ ) {
		       	if( raw[i] != outs[i] ) {
				std::cout << "ERROR: byte " << i << " es ";
				std::cout << (int)raw[i] << " (esperado: " << outs[i] << ")\n";
			}
		}
	}
}

void test_5()
{
	std::cout << "Corriendo test_5().\n";

	OutputBitStream obs;
	obs.append( 2, 0 );
	obs.append( 3, 0 );
	obs.append( 1, 1 );
	obs.skip();
	obs.append( 8, 2 );
	obs.append( 8, 2 );
	obs.append( 1, 0 );
	obs.append( 1, 0 );
	obs.append( 1, 1 );
	obs.append( 1, 0 );
	obs.append( 1, 1 );
	obs.append( 1, 1 );
	obs.append( 1, 1 );
	obs.append( 1, 0 );
	const unsigned char* raw = obs.get_data();
	if( obs.get_size() != 4 )
		std::cout << "ERROR: tamano " << obs.get_size() << " (esperado: 3 )\n";
	else {
		int outs[4] = { 0x04, 0x02, 0x02, 0x2E };
		for( int i = 0; i < 4; i++ ) {
		       	if( raw[i] != outs[i] ) {
				std::cout << "ERROR: byte " << i << " es ";
				std::cout << (int)raw[i] << " (esperado: " << outs[i] << ")\n";
			}
		}
	}

}

void test_6()
{
	std::cout << "Corriendo test_6().\n";

	OutputBitStream obs;
	OutputBitStream obs2;

	obs.append( 2, 0 );
	obs.append( 3, 0 );
	obs.append( 1, 1 );
	//obs.skip();
	obs2.append( 8, 2 );
	obs2.append( 8, 2 );
	obs2.append( 1, 0 );
	obs2.append( 1, 0 );
	obs2.append( 1, 1 );
	obs.append( obs2 );
	obs.append( 1, 0 );
	obs.append( 1, 1 );
	obs.append( 1, 1 );
	obs.append( 1, 1 );
	obs.append( 1, 0 );
	const unsigned char* raw = obs.get_data();
	if( obs.get_size() != 4 )
		std::cout << "ERROR: tamano " << obs.get_size() << " (esperado: 3 )\n";
	else {
		int outs[4] = { 0x04, 0x02, 0x02, 0x2E };
		for( int i = 0; i < 4; i++ ) {
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
	test_4();
	test_5();
	test_6();
	return 0;
}

