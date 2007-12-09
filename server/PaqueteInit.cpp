#include "PaqueteInit.h"

namespace {
	const char ID = 0;
}

PaqueteInit::PaqueteInit() : Paquete( ID )
{

}	

PaqueteInit::PaqueteInit( bool pac, S_ptr<MapaBajoNivel> m )
	: Paquete( ID ), mapa( m )
{
	esPacman = pac;
}

void PaqueteInit::deserialize( InputBitStream& bs )
{
	esPacman = ( bs.read( 1 ) == 0 ); // Lectura del rol desde el campo auxiliar.
	bs.skip(); // Saltea el resto del campo auxiliar.

	int ancho = bs.read( 8 );
	int alto = bs.read( 8 );
	int long_aristas = ancho * alto * 2;
	char* conexiones = bs.read_block( long_aristas );
	bs.skip();
//	generar_mapa( 
}

void PaqueteInit::serialize( OutputBitStream& bs )
{
	Paquete::serialize( bs ); // Escribe version de protocolo e ID de paquete.

	bs.append( 1, esPacman ? 0 : 1 ); // Escribe campo auxiliar.
	bs.skip();

	bs.append( 8, mapa->get_ancho() );
	bs.append( 8, mapa->get_alto() );

	bs.grow( mapa->get_ancho()*mapa->get_alto()*2 );

	for( unsigned int y=0; y < mapa->get_alto(); y++ ) {
		// Aristas verticales
		for( unsigned int x=0; x < mapa->get_ancho(); x++ ){
			Posicion p( x, y );
			bs.append( 1, !( mapa->get_estructural( p )->get_arriba().es_nulo() ) );
		}
		// Aristas horizontales
		for( unsigned int x=0; x < mapa->get_ancho(); x++ ) {
			Posicion p( x, y );
			bs.append( 1, !( mapa->get_estructural( p )->get_derecha().es_nulo() ) );
		}
	}

	bs.skip();
	
	// TODO: Escribir elementos del mapa.
	bs.append( 8, 0 );
}

Operacion * PaqueteInit::get_operacion(){
	//TODO
}
