
#include "Configuracion.h"
#include <fstream>

void Configuracion::set_conf( std::string nom, ConfValue v )
{
	confs[ nom ] = v;	
}

ConfValue Configuracion::get_conf( std::string nom )
{
	Mapa::iterator it = confs.find( nom );
	if( it != confs.end() )
		return (*it).second;
	throw "TODO: nombre de opcion no disponible.";
}

void Configuracion::load_conf( std::string ruta )
{
	std::ifstream file( ruta.c_str() );

}

