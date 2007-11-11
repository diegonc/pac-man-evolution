#ifndef __MAPA_H__
#define __MAPA_H__

#include "Personaje.h"

class Mapa
{
	public:
		virtual ~Mapa();

		virtual void mover( int id, Direccion dir ) = 0;

		virtual Personaje& get_personaje( int id ) = 0;
};

#endif /* __MAPA_H__ */
