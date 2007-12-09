#include "PaqueteInit.h"
#include "MapImpSet.h"
#include "EstructuralPasillo.h"

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
	mapa = S_ptr<MapaBajoNivel>( new MapaImpSet( ancho, alto ) );
	int long_aristas = ancho * alto * 2;
	bs.grow( long_aristas );
	for( int y=0; y < alto; y++ ) {
		for( int x=0; x < ancho; x++ )
			if( bs.read(1) != 0 )
				agregar_arista( x, y, true );
		for( int x=0; x < ancho; x++ )
			if( bs.read(1) != 0 )
				agregar_arista( x, y, false );
	}
	bs.skip();
	unsigned int num_elems = bs.read( 16 );
}

void PaqueteInit::agregar_arista( int x, int y, bool norte )
{
	Posicion origen( x, y );
	Posicion destino;
	S_ptr<EstructuralUnitario> esO = mapa->get_estructural( origen );

	if( esO.es_nulo() ) {
		esO = new EstructuralPasillo( Comestible::quesito, origen );
		mapa->agregar_estructural( esO );
	}

	if( norte ) {
		int alto = mapa->get_alto();
		destino.set_y( ( y - 1 + alto ) % alto );
	}else {
		int ancho = mapa->get_ancho();
		destino.set_x( ( x + 1 + ancho ) % ancho ); 
	}

	S_ptr<EstructuralUnitario> esD = mapa->get_estructural( destino );
	if( esD.es_nulo() ) {
		esD = new EstructuralPasillo( Comestible::quesito, destino );
		mapa->agregar_estructural( esD );
	}

	if( norte ) {
		esO->set_arriba( esD );
		esD->set_abajo( esO );
	} else {
		esO->set_derecha( esD );
		esD->set_izquierda( esO );
	}
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
