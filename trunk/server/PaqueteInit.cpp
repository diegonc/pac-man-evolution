#include "PaqueteInit.h"

namespace {
	const char ID = 0;
}

PaqueteInit::PaqueteInit( Tipo_Jugador j, MapaBajoNivel& m ) : Paquete( ID ), mapa( m )
{
	esPacman = ( j->get_personaje()->get_tipo() == Personaje::pacman );
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

	bs.append( 1, esPacman ); // Escribe campo auxiliar.
	bs.skip();

	bs.append( 8, mapa.get_ancho() );
	bs.append( 8, mapa.get_alto() );

	bs.grow( mapa.get_ancho()*mapa.get_alto()*2 );

	for( unsigned int y=0; y < mapa.get_alto(); y++ ) {
		// Aristas verticales
		for( unsigned int x=0; x < mapa.get_ancho(); x++ ){
			Posicion p( x, y );
			bs.append( 1, !( mapa.get_estructural( p )->get_arriba().es_nulo() ) );
		}
		// Aristas horizontales
		for( unsigned int x=0; x < mapa.get_ancho(); x++ ) {
			Posicion p( x, y );
			bs.append( 1, !( mapa.get_estructural( p )->get_derecha().es_nulo() ) );
		}
	}

	bs.skip();
	
	// TODO: Escribir elementos del mapa.
}
