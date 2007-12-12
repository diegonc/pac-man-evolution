#include "test-equal.h"
#include "opt/Configuracion.h"
#include <iostream>

void TestConfEqual::run( std::ostream& o )
{
	ConfValue destino;

	_status = true;

	{ ConfValue origen( 5 );
	destino = origen;
	if(! ( destino == origen ) ) {
		_status = false;
		o << "\tOrigen: "; origen.dump( o );
		o << "\n\tDestino: "; destino.dump( o );
		o << '\n';
	}

	}

	{ ConfValue origen( true );
	destino = origen;
	if(! ( destino == origen ) ) {
		_status = false;
		o << "\tOrigen: "; origen.dump( o );
		o << "\n\tDestino: "; destino.dump( o );
		o << '\n';
	}

	}

	{ ConfValue origen( "hola mundo" );
	destino = origen;
	if(! ( destino == origen ) ) {
		_status = false;
		o << "\tOrigen: "; origen.dump( o );
		o << "\n\tDestino: "; destino.dump( o );
		o << '\n';
	}

	}
}
