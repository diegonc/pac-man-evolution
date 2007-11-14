#ifndef __MAPAIMP_H__
#define __MAPAIMP_H__

#include "Mapa.h"
#include "Jugador.h"

/** @brief Implementa una interfaz de mapa
 *
 */

class MapaImp : public Mapa
{
	public:
		~MapaImp();

		void mover( int id, Direccion dir );

		S_ptr<Jugador> get_jugador( int id );
	
		S_ptr<Jugador> get_jugador(int pos_x, int pos_y);
};

#endif /* __MAPAIMP_H__ */
