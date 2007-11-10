#include "MundoMockImpl.h"
#include "MapaMockImpl.h"

Mundo* MundoMockImpl::instance = 0;

Mundo& MundoMockImpl::get_instance()
{
	if( !instance )
		instance = new MundoMockImpl();

	return *instance;
}

void MundoMockImpl::destroy()
{
	if( instance )
		delete instance;
}

MundoMockImpl::MundoMockImpl()
{
	mapas.push_back( new MapaMockImpl() );
	cursor = mapas.begin();
}

MundoMockImpl::~MundoMockImpl()
{
	std::list<Mapa*>::iterator it = mapas.begin();
	while( it != mapas.end() )
		delete *(it++);
}

Mapa* MundoMockImpl::get_mapa_activo()
{
	if( cursor == mapas.end() )
		return 0;

	return *cursor;
}
