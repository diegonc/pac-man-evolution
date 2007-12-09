#include "PaqueteInit.h"
#include "MapImpSet.h"
#include "EstructuralPasillo.h"
#include "EstructuralCasaFantasma.h"
#include "Direccion.h"
#include "Posicion.h"

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
	bs.grow( num_elems*24 );
	for(unsigned int i=0; i < num_elems; i++ ) {
		int tipo = bs.read( 6 );
		int orient = bs.read( 2 );
		int pos = bs.read( 16 );
		Posicion p( pos % ancho, pos / ancho);
		S_ptr<EstructuralUnitario> e = mapa->get_estructural( p );
		switch( tipo ) {
			case 0:
				if( e->get_tipo() == EstructuralUnitario::Pasillo ) {
					EstructuralPasillo* ep = (EstructuralPasillo *) &(*e);
					ep->set_salida_pacman();
				}
				break;
			case 1: {
				S_ptr<EstructuralUnitario> c( new EstructuralCasaFantasma( p ) );
				reemplazar_estructural( c ); 
				}
				break;
			case 2:
				if( e->get_tipo() == EstructuralUnitario::Pasillo ) {
					EstructuralPasillo* ep = (EstructuralPasillo*) &(*e);
					ep->set_comida( Comestible::power_up );
				}
				break;
			case 3:
				if( e->get_tipo() == EstructuralUnitario::Pasillo ) {
					EstructuralPasillo* ep = (EstructuralPasillo*) &(*e);
					ep->set_comida( Comestible::frutita );
				}
				break;
		}
	}
}

void PaqueteInit::escribir_estructural( S_ptr<EstructuralUnitario>& e, OutputBitStream& bs )
{
	if( e.es_nulo() ) return;

	bs.append( 6, (int)e->get_tipo() );
	bs.append( 2, Direccion::Norte );
	Posicion& p = e->get_posicion();
	int pos = (int)p.get_y() * mapa->get_ancho() + (int)p.get_x();
	bs.append( 16, pos );
}

bool PaqueteInit::escribir_comestible( S_ptr<Comestible>& c, OutputBitStream& bs )
{
	if( c.es_nulo() ) return false;
	if( c->get_tipo() == Comestible::quesito ) return false;

	bs.append( 6, (int)c->get_tipo() );
	bs.append( 2, Direccion::Norte );
	Posicion& p = c->get_posicion();
	int pos = (int)p.get_y() * mapa->get_ancho() + (int)p.get_x();
	bs.append( 16, pos );
	return true;
}

void PaqueteInit::reemplazar_estructural( S_ptr<EstructuralUnitario>& e )
{
	Posicion p( e->get_posicion() );
	S_ptr<EstructuralUnitario> actual = mapa->get_estructural( p );
	mapa->agregar_estructural( e );
	if( !actual.es_nulo() ) {
		if( ! actual->get_arriba().es_nulo() ) {
			e->set_arriba( actual->get_arriba() );
			actual->get_arriba()->set_abajo( e );
		}
		if( ! actual->get_derecha().es_nulo() ) {
			e->set_derecha( actual->get_derecha() );
			actual->get_derecha()->set_izquierda( e );
		}
		if( ! actual->get_abajo().es_nulo() ) {
			e->set_abajo( actual->get_abajo() );
			actual->get_abajo()->set_arriba( e );
		}
		if( ! actual->get_izquierda().es_nulo() ) {
			e->set_izquierda( actual->get_izquierda() );
			actual->get_izquierda()->set_derecha( e );
		}
	}
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
	/* TODO: supone casa fantasma y salida unica. */
	S_ptr<EstructuralUnitario> casa;
	S_ptr<EstructuralUnitario> salida;
	Paquete::serialize( bs ); // Escribe version de protocolo e ID de paquete.

	bs.append( 1, esPacman ? 0 : 1 ); // Escribe campo auxiliar.
	bs.skip();

	bs.append( 8, mapa->get_ancho() );
	bs.append( 8, mapa->get_alto() );

	bs.grow( mapa->get_ancho()*mapa->get_alto()*2 );

	S_ptr<EstructuralUnitario> e;
	for( unsigned int y=0; y < mapa->get_alto(); y++ ) {
		// Aristas verticales
		for( unsigned int x=0; x < mapa->get_ancho(); x++ ){
			Posicion p( x, y );
			e = mapa->get_estructural( p );
			if(!e.es_nulo() ) {
				if( e->get_tipo() == EstructuralUnitario::Casa_Fantasma ) casa = e;
				if( e->get_tipo() == EstructuralUnitario::Salida_Pacman ) salida = e;
				bs.append( 1, !( e->get_arriba().es_nulo() ) );
			}
		}
		// Aristas horizontales
		for( unsigned int x=0; x < mapa->get_ancho(); x++ ) {
			Posicion p( x, y );
			e = mapa->get_estructural( p );
			if(!e.es_nulo() )
				bs.append( 1, !( e->get_derecha().es_nulo() ) );
		}
	}
	
	bs.skip();
	
	// TODO: Escribir elementos del mapa.
	OutputBitStream elems;
	int elem_count = 2;
	
	escribir_estructural( casa, elems );
	escribir_estructural( salida, elems );
	
	std::list< S_ptr<Comestible> > comestibles = mapa->get_comestibles();
	std::list<S_ptr<Comestible> >::iterator it = comestibles.begin();
	for( ; it != comestibles.end(); ++it )
		if( escribir_comestible( *it, elems ) )
			elem_count++;

	bs.append( 16, elem_count );
	bs.append( elems );
}

Operacion * PaqueteInit::get_operacion(){
	//TODO
}
