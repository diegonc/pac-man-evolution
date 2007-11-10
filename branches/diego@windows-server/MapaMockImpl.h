#ifndef __MAPAMOCKIMPL_H__
#define __MAPAMOCKIMPL_H__

#include "Mapa.h"

class MapaMockImpl : Mapa
{
	public:
		void mover( int id, Mapa::Direccion dir );
};

#endif /* __MAPAMOCKIMPL_H__ */
