#include "test_pstart.h"
#include "server/PaqueteStart.h"
#include "server/OutputBitStream.h"

namespace {
	char esperado[] = { 8, 0, 1 };
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
}

void TestPaqueteStart::run( std::ostream& o )
{
	OutputBitStream obs;
	PaqueteStart p( 1 );
	p.serialize( obs );
	_status = validar( obs.get_data(), obs.get_size(), o );	
}
