#include "test-load.h"
#include "opt/Configuracion.h"
#include <iostream>

namespace {

	void init_conf( Configuracion& conf )
	{
		conf.set_conf( "mundo", ConfValue( "unmundo.mdo" ) );
		//conf.set_conf( "direccion", "0.0.0.0" );
		//conf.set_conf( "min-jugadores", ConfValue(2) );
		//conf.set_conf( "max-jugadores", ConfValue(5) );
	}

	bool validar( const Configuracion& c, std::ostream& o )
	{
		Configuracion conf;

		init_conf( conf );
		bool res = ( conf == c );
		if( !res )
			c.dump( o );

		return res;
	}
}

void TestConfLoad::run( std::ostream& o )
{
	Configuracion conf;

	conf.load_conf( "../../opt/sample.conf" );

	_status = validar( conf, o );
}
