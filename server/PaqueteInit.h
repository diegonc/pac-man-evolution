#ifndef __PAQUETEINIT_H__
#define __PAQUETEINIT_H__

#include "Paquete.h"
#include "MapaBajoNivel.h"
#include "../common/smart_pointer.h"

class PaqueteInit : public Paquete
{
	private:
		/** @brief Determina si el cliente que recibe el paquete es el pacman o no.
		 */
		bool esPacman;

		/** @brief MapaBajoNivel en el que se desarrolla el juego.
		 */
		S_ptr<MapaBajoNivel> mapa;

	public:
		/** Crea un paquete apto para deserializar. */
		PaqueteInit();

		/** Crea un paquete apto para serializar. */
		PaqueteInit( bool pacman, MapaBajoNivel& m );

		void serialize( OutputBitStream& bs );

		void deserialize( InputBitStream& bs );
};

#endif /* _PAQUETEINIT_H__ */
