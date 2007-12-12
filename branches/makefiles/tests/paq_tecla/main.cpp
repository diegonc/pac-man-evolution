#include "../../server/PaqueteTecla.h"
#include "../../server/OutputBitStream.h"
#include "../../server/InputBitStream.h"
#include "../../server/MemoryReader.h"
#include "../../server/KeyOp.h"
#include <iostream>

#define DATOS_PRUEBA_S 1

void test_arriba()
{
	std::cout << "Corriendo test_arriba()\n";
	PaqueteTecla p( 1, KeyOp::arriba );
	OutputBitStream obs;
	unsigned char raw[1] = { 0x28 };

	p.serialize( obs );
	
	if( DATOS_PRUEBA_S != obs.get_size() ) {
		std::cout << "ERROR: Paquete se serializo en:\n\t\t";
	        std::cout << obs.get_size() << "bytes ";
		std::cout << "( esperados: " << DATOS_PRUEBA_S << "bytes )\n";
	} else {
		const unsigned char* s = obs.get_data();
		for( int i=0; i < DATOS_PRUEBA_S; i++ ) {
			if( raw[i] != s[i] ) {
				std::cout << "ERROR: byte " << i << " es "  << (int) s[i];
				std::cout << " ( esperado: " << (int)raw[i] << ")\n";
			}
		}
	}
}

void test_abajo()
{
	std::cout << "Corriendo test_abajo().\n";
	PaqueteTecla p( 1, KeyOp::abajo );
	OutputBitStream obs;
	unsigned char raw[1] = { 0x29 };

	p.serialize( obs );
	
	if( DATOS_PRUEBA_S != obs.get_size() ) {
		std::cout << "ERROR: Paquete se serializo en:\n\t\t";
	        std::cout << obs.get_size() << "bytes ";
		std::cout << "( esperados: " << DATOS_PRUEBA_S << "bytes )\n";
	} else {
		const unsigned char* s = obs.get_data();
		for( int i=0; i < DATOS_PRUEBA_S; i++ ) {
			if( raw[i] != s[i] ) {
				std::cout << "ERROR: byte " << i << " es "  << (int) s[i];
				std::cout << " ( esperado: " << (int)raw[i] << ")\n";
			}
		}
	}
}

void test_derecha()
{
	std::cout << "Corriendo test_derecha()\n";
	PaqueteTecla p( 1, KeyOp::derecha );
	OutputBitStream obs;
	unsigned char raw[1] = { 0x2B };

	p.serialize( obs );
	
	if( DATOS_PRUEBA_S != obs.get_size() ) {
		std::cout << "ERROR: Paquete se serializo en:\n\t\t";
	        std::cout << obs.get_size() << "bytes ";
		std::cout << "( esperados: " << DATOS_PRUEBA_S << "bytes )\n";
	} else {
		const unsigned char* s = obs.get_data();
		for( int i=0; i < DATOS_PRUEBA_S; i++ ) {
			if( raw[i] != s[i] ) {
				std::cout << "ERROR: byte " << i << " es "  << (int) s[i];
				std::cout << " ( esperado: " << (int)raw[i] << ")\n";
			}
		}
	}
}

void test_izquierda()
{
	std::cout << "Corriendo test_izquierda()\n";
	PaqueteTecla p( 1, KeyOp::izquierda );
	OutputBitStream obs;
	unsigned char raw[1] = { 0x2A };

	p.serialize( obs );
	
	if( DATOS_PRUEBA_S != obs.get_size() ) {
		std::cout << "ERROR: Paquete se serializo en:\n\t\t";
	        std::cout << obs.get_size() << "bytes ";
		std::cout << "( esperados: " << DATOS_PRUEBA_S << "bytes )\n";
	} else {
		const unsigned char* s = obs.get_data();
		for( int i=0; i < DATOS_PRUEBA_S; i++ ) {
			if( raw[i] != s[i] ) {
				std::cout << "ERROR: byte " << i << " es "  << (int) s[i];
				std::cout << " ( esperado: " << (int)raw[i] << ")\n";
			}
		}
	}
}

int main()
{
	test_arriba();
	test_abajo();
	test_izquierda();
	test_derecha();
	return 0;
}
