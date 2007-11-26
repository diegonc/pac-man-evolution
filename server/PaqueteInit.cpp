#include "PaqueteInit.h"

namespace {
	const char ID = 0;
}

PaqueteInit::PaqueteInit() : Paquete( ID )
{
}

void PaqueteInit::deserialize( BitStream& bs )
{
	esPacman = ( bs.read( 1 ) == 0 ); // Lectura del rol desde el campo auxiliar.
	bs.skip(); // Saltea el resto del campo auxiliar.

	grafo_ancho = bs.read( 8 );
	grafo_alto = bs.read( 8 );

	int long_aristas = grafo_ancho * grafo_alto * 2;
	bs.grow( long_aristas ); // Precarga el bloque de datos de las aristas
	grafo_aristas = bs.read_block( long_aristas );
	bs.skip();
}
