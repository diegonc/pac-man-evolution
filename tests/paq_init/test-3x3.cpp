#include "test-3x3.h"
#include "../../server/PaqueteInit.h"
#include "../../server/OutputBitStream.h"
#include "../../server/InputBitStream.h"
#include "../../server/MemoryReader.h"
#include "../../server/MapaBajoNivel.h"
#include "../../server/MapImpSet.h"
#include "../../server/EstructuralPasillo.h"
#include "../../server/Posicion.h"

namespace {
	char esperado[] = { 0, 3, 3, 18, 0, 0, 0, 3, 12, 0, 0, 8, 0, 1,
       			    12, 0, 3 };
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
		MapaBajoNivel* m = new MapaImpSet( 3, 3 );
		Posicion p = Posicion(0,0);
		S_ptr<EstructuralUnitario> p0( new EstructuralPasillo( Comestible::frutita, p ));
		p = Posicion(1,0);
		S_ptr<EstructuralUnitario> p1( new EstructuralPasillo( Comestible::power_up, p ));
		p = Posicion(0,1);
		S_ptr<EstructuralUnitario> p2( new EstructuralPasillo( Comestible::frutita, p ));
		
		p0->set_derecha( p1 );
		p1->set_izquierda( p0 );
		p2->set_arriba( p0 );
		p0->set_abajo( p2 );

		m->agregar_estructural( p0 );
		m->agregar_estructural( p1 );
		m->agregar_estructural( p2 );
		return m;
	}
}

void TestPaqInitPruebaBad::run( std::ostream& o )
{
	S_ptr<MapaBajoNivel> map( mapa_de_prueba() );
	PaqueteInit p( true, map );
	OutputBitStream obs;
	p.serialize( obs );
	_status = validar( obs.get_data(), obs.get_size(), o );	
}
