#include "MundoBasicImp.h"
#include "MapaImp.h"

MundoBasicImp* MundoBasicImp::instance = 0;

MundoBasicImp::MundoBasicImp()
{
	mapas.push_back( new MapaImp() );
}

MundoBasicImp::~MundoBasicImp()
{
	delete mapas.back();
}

Mundo& MundoBasicImp::get_instance()
{
	if( ! instance )
		instance = new MundoBasicImp();

	return *instance;
}

void MundoBasicImp::destroy()
{
	if( instance ) {
		delete instance;
		instance = 0;
	}
}

Mapa& MundoBasicImp::get_mapa_activo()
{
	return *mapas.back();
}
