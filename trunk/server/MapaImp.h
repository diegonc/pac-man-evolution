#ifndef __MAPAIMP_H__
#define __MAPAIMP_H__

#include "Mapa.h"

class MapaImp : public Mapa
{
	public:
		~MapaImp();

		void mover( int id, Direccion dir );

		Personaje& get_personaje( int id );
};

#endif /* __MAPAIMP_H__ */
