#include "PaqueteInit.h"

namespace {
	const char ID = 0;
}

PaqueteInit::PaqueteInit( Mapa& m ) : Paquete( ID ), mapa( m )
{
}

void PaqueteInit::deserialize( InputBitStream& bs )
{
	esPacman = ( bs.read( 1 ) == 0 ); // Lectura del rol desde el campo auxiliar.
	bs.skip(); // Saltea el resto del campo auxiliar.

	grafo_ancho = bs.read( 8 );
	grafo_alto = bs.read( 8 );

	int long_aristas = grafo_ancho * grafo_alto * 2;
        
	grafo_aristas = bs.read_block( long_aristas );
	bs.skip();

	// TODO: esto solo tiene sentido en el programa del cliente.
}

void PaqueteInit::serialize( OutputBitStream& bs )
{
	Paquete::serialize( bs ); // Escribe version de protocolo e ID de paquete.

	bs.write( 1, esPacman ); // Escribe campo auxiliar.
	bs.skip();

	bs.write( 8, mapa.get_ancho() );
	bs.write( 8, mapa.get_alto() );

	bs.grow( mapa.get_ancho()*mapa.get_alto()*2 );

	for( unsigned int y=0; y < mapa.get_alto(); y++ ) {
		// Aristas verticales
		for( unsigned int x=0; x < mapa.get_ancho(); x++ ){
			Posicion p( x, y );
			bs.write( 1, !( mapa.get_estructural( p )->get_arriba().es_nulo() ) );
		}
		// Aristas horizontales
		for( unsigned int x=0; x < mapa.get_ancho(); x++ ) {
			Posicion p( x, y );
			bs.write( 1, !( mapa.get_estructural( p )->get_derecha().es_nulo() ) );
		}
	}

	bs.skip();
	
	// TODO: Escribir elementos del mapa.
}
