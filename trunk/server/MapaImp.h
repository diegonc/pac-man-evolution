#ifndef __MAPAIMP_H__
#define __MAPAIMP_H__

#include "Mapa.h"

class MapaImp : public Mapa
{
	public:
		~MapaImp();

		void mover( int id, Direccion dir );

		S_ptr<Jugador> get_personaje( int id );
	
		S_ptr<Jugador> get_personaje(int pos_x, int pos_x);
};

#endif /* __MAPAIMP_H__ */
