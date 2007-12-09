#include "../../server/PaqueteInit.h"
#include "../../server/OutputBitStream.h"
#include "../../server/InputBitStream.h"
#include "../../server/MemoryReader.h"
#include "../../server/MapaBajoNivel.h"
#include "../../server/MapImpSet.h"
#include "../../server/EstructuralPasillo.h"
#include "../../server/Posicion.h"
#include <iostream>

MapaBajoNivel* mapa_de_prueba()
{
	MapaBajoNivel* m = new MapaImpSet( 2, 2 );
	Posicion p = Posicion(0,0);
	S_ptr<EstructuralUnitario> p0( new EstructuralPasillo( Comestible::quesito, p ));
	p = Posicion(0,1);
	S_ptr<EstructuralUnitario> p1( new EstructuralPasillo( Comestible::quesito, p ));
	p = Posicion(1,0);
	S_ptr<EstructuralUnitario> p2( new EstructuralPasillo( Comestible::quesito, p ));
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

unsigned char* datos_de_prueba()
{
	#define DATOS_PRUEBA_S 5
	static unsigned char raw[DATOS_PRUEBA_S] = {
	       	4 /* fantasma */, 2, 2, 46, 0 };
	return raw;
}

int main()
{
	MapaBajoNivel* map = mapa_de_prueba();
	PaqueteInit p( false, *map );
	OutputBitStream obs;
	unsigned char* raw = datos_de_prueba();

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
	delete map;
	return 0;
}
