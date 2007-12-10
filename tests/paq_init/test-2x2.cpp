#include "test-2x2.h"
#include "../../server/PaqueteInit.h"
#include "../../server/OutputBitStream.h"
#include "../../server/InputBitStream.h"
#include "../../server/MemoryReader.h"
#include "../../server/MapaBajoNivel.h"
#include "../../server/MapImpSet.h"
#include "../../server/EstructuralPasillo.h"
#include "../../server/Posicion.h"
#include <iostream>

namespace {
	char esperado[] = { 4 /* fantasma */, 2, 2, 46, 0, 2, 12, 0, 1, 
		            8, 0, 2 };
	#define ESPERADO_LEN	( sizeof(esperado)/sizeof(char) )

	bool validar( const unsigned char* s, unsigned int n, std::ostream& o )
	{
	    bool ok = true;
	    if( ESPERADO_LEN != n ) {
	        o << "ERROR: Paquete se serializo en:\n\t\t";
	        o << n << "bytes ";
		o << "( esperados: " << ESPERADO_LEN << "bytes )\n";
		ok = false;
	    } else {
	        for( int i=0; i < ESPERADO_LEN; i++ ) {
	            if( esperado[i] != s[i] ) {
	                o << "ERROR: byte " << i << " es " << (int) s[i];
	                o << " ( esperado: " << (int)esperado[i] << ")\n";
			ok = false;
	            }
	        }
	    }
	    return ok;
	}

	MapaBajoNivel* mapa_de_prueba()
	{
		MapaBajoNivel* m = new MapaImpSet( 2, 2 );
		Posicion p = Posicion(0,0);
		S_ptr<EstructuralUnitario> p0( new EstructuralPasillo( Comestible::quesito, p ));
		p = Posicion(1,0);
		S_ptr<EstructuralUnitario> p1( new EstructuralPasillo( Comestible::frutita, p ));
		p = Posicion(0,1);
		S_ptr<EstructuralUnitario> p2( new EstructuralPasillo( Comestible::power_up, p ));
		p = Posicion(1,1);
		S_ptr<EstructuralUnitario> p3( new EstructuralPasillo( Comestible::quesito, p ));
		
		p0->set_derecha( p1 );
		p2->set_arriba( p0 );
		p2->set_derecha( p3 );
		p3->set_arriba( p1 );

		m->agregar_estructural( p0 );
		m->agregar_estructural( p1 );
		m->agregar_estructural( p2 );
		m->agregar_estructural( p3 );
		return m;
	}
}

void TestPaqInitPruebaCircular::run( std::ostream& o )
{
	S_ptr<MapaBajoNivel> map( mapa_de_prueba() );
	PaqueteInit p( false, map );
	OutputBitStream obs;
	p.serialize( obs );
	_status = validar( obs.get_data(), obs.get_size(), o );	
}
