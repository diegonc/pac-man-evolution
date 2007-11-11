#include "MundoBasicImp.h"
#include "MapaImp.h"

S_ptr<Mundo> MundoBasicImp::instancia;

MundoBasicImp::MundoBasicImp()
{
	mapas.push_back( new MapaImp() );
}

MundoBasicImp::~MundoBasicImp()
{
	delete mapas.back();
}

S_ptr<Mundo> MundoBasicImp::get_instancia()
{
	if( instancia.es_nulo() )
		instancia = S_ptr<Mundo>(new MundoBasicImp());

	return instancia;
}

Mapa& MundoBasicImp::get_mapa_activo()
{
	return *mapas.back();
}
