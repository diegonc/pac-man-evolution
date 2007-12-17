#include "PaqueteInitCommon.h"

#include "MapImpSet.h"
#include "EstructuralPasillo.h"
#include "EstructuralCasaFantasma.h"
#include "Direccion.h"
#include "Posicion.h"
#include "Operacion.h"
#include "MundoBajoNivel.h"

namespace {
	const char ID = 0;
}

PaqueteInitCommon::PaqueteInitCommon() : Paquete( ID )
{

}	

PaqueteInitCommon::PaqueteInitCommon( bool pac, S_ptr<MapaBajoNivel> m )
	: Paquete( ID ), mapa( m )
{
	esPacman = pac;
}

void PaqueteInitCommon::deserialize( InputBitStream& bs )
{

	
	esPacman = ( bs.read( 1 ) == 0 ); // Lectura del rol desde el campo auxiliar.
	bs.skip(); // Saltea el resto del campo auxiliar.
	int ancho = bs.read( 8 );
	int alto = bs.read( 8 );
//	std::cout << "ancho: " << ancho << " alto: " << alto << std::endl << std::flush;
	mapa = S_ptr<MapaBajoNivel>( new MapaImpSet( ancho, alto ) );
	int long_aristas = ancho * alto * 2;
//	std::cout << "long aristas: " << long_aristas << std::endl << std::flush;
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
//	std::cout << "num elems: " << num_elems << std::endl << std::flush;
	bs.grow( num_elems*24 );
	for(unsigned int i=0; i < num_elems; i++ ) {
		int tipo = bs.read( 6 );
//		std::cout << "tipo recibido: " << tipo << std::endl << std::flush;
		bs.read( 2 ); //orientacion ?
		int pos = bs.read( 16 );
//		std::cout << "pos recibida: " << pos << std::endl << std::flush;
		Posicion p( pos % ancho, pos / ancho);
		S_ptr<EstructuralUnitario> e = mapa->get_estructural( p );
		if (!e.es_nulo()){
			switch( tipo ) {
				case 0 /* Salida Pacman */:
					if( e->get_tipo() == EstructuralUnitario::Pasillo ) {
						EstructuralPasillo* ep = (EstructuralPasillo *) &(*e);
						ep->set_salida_pacman();
					}
					break;
				case 1 /* Casa Fantasma */: {
						S_ptr<EstructuralUnitario> c( new EstructuralCasaFantasma( p ) );
						reemplazar_estructural( c ); 
					}
					break;
				case 2 /* Power up */:
					if( e->get_tipo() == EstructuralUnitario::Pasillo ) {
						remplazar_comestible(e,Comestible::power_up);
//						ep->set_comida( Comestible::power_up );
//						std::cout << "seteando power up en: " << p << std::endl << std::flush;
					}
					break;
				case 3 /* Bonus */:
					if( e->get_tipo() == EstructuralUnitario::Pasillo ) {
						remplazar_comestible(e,Comestible::frutita);
						//ep->set_comida( Comestible::frutita );
//						std::cout << "seteando frutita en: " << p << std::endl << std::flush;
					}
					break;
			}
		}
	}
		
}
void PaqueteInitCommon::remplazar_comestible(S_ptr<EstructuralUnitario>& e ,Comestible::Enum_Comestible tipoCom )
{
	if( !e.es_nulo() ) {
		Posicion p( e->get_posicion() );	
		unsigned int fila = (unsigned int) floor(p.get_y());
		unsigned int col =  (unsigned int) floor(p.get_x());
		unsigned int key=(fila * mapa->get_ancho()) + col;
		mapa->refresh(key,tipoCom);
		
	}		
}


bool PaqueteInitCommon::escribir_estructural( S_ptr<EstructuralUnitario>& e, OutputBitStream& bs )
{
	if( e.es_nulo() ) return false;

	bs.append( 6, (int)e->get_tipo() );
	bs.append( 2, Direccion::Norte);	
	Posicion& p = e->get_posicion();
	unsigned int pos = (unsigned int)p.get_y() * mapa->get_ancho() + (unsigned int)p.get_x();
	bs.append( 16, pos );
	return true;
}

bool PaqueteInitCommon::escribir_comestible( S_ptr<Comestible>& c, OutputBitStream& bs )
{
	/* 
	 * Ojo que el tipo que se manda NO es el mismo que el tipo del
	 * comestible. coinciden solo en el paquete status.
	 */
	if( c.es_nulo() ) return false;
	if( c->get_tipo() == Comestible::frutita )
		bs.append( 6, 3 );
	else if( c->get_tipo() == Comestible::power_up )
		bs.append( 6, 2 );
	else return false;
	bs.append( 2, Direccion::Norte );	
	Posicion& p = c->get_posicion();
	
	unsigned int pos = (unsigned int)p.get_y() * mapa->get_ancho() + (unsigned int)p.get_x();
	bs.append( 16, pos );
	
	return true;
}

void PaqueteInitCommon::reemplazar_estructural( S_ptr<EstructuralUnitario>& e )
{
	Posicion p( e->get_posicion() );
	S_ptr<EstructuralUnitario> actual = mapa->get_estructural( p );
	mapa->agregar_estructural( e );
	if( !actual.es_nulo() ) {
		unsigned int fila = (unsigned int) floor(p.get_y());
		unsigned int col =  (unsigned int) floor(p.get_x());
		unsigned int key=(fila * mapa->get_ancho()) + col;
		mapa->refresh(key);
//		mapa->quitar_comestible(actual->get_comida());
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

void PaqueteInitCommon::agregar_arista( int x, int y, bool norte )
{
	Posicion origen( x, y );
	Posicion destino( x, y );
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

void PaqueteInitCommon::serialize( OutputBitStream& bs )
{

	std::list< S_ptr<EstructuralUnitario> > casa;
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
				if( e->get_tipo() == EstructuralUnitario::Casa_Fantasma ) casa.push_back(e);
				if( e->get_tipo() == EstructuralUnitario::Salida_Pacman ) salida = e;
				bs.append( 1, !( e->get_arriba().es_nulo() ) );
			}else
				bs.append( 1, 0);
		}
		// Aristas horizontales
		for( unsigned int x=0; x < mapa->get_ancho(); x++ ) {
			Posicion p( x, y );
			e = mapa->get_estructural( p );
			if(!e.es_nulo()){
				bs.append( 1, !( e->get_derecha().es_nulo() ) );
			}else
				bs.append( 1, 0);
		}
	}
	
	bs.skip();
	
	OutputBitStream elems;
	int elem_count = 0;
	for (std::list< S_ptr<EstructuralUnitario> >::iterator it=casa.begin();it!=casa.end();++it){
		if( escribir_estructural( *it, elems ) ) elem_count++;
	}
	if( escribir_estructural( salida, elems ) ) elem_count++;
	
	std::list< S_ptr<Comestible> > comestibles = mapa->get_comestibles();
	std::list<S_ptr<Comestible> >::iterator it = comestibles.begin();
	for( ; it != comestibles.end(); ++it )		
		if( escribir_comestible( *it, elems ) )
			elem_count++;

	bs.append( 16, elem_count );
	bs.append( elems );		
	
}
