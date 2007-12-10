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

		void agregar_arista( int x, int y, bool norte );

		void reemplazar_estructural( S_ptr<EstructuralUnitario>& e );

		bool escribir_estructural( S_ptr<EstructuralUnitario>& e, OutputBitStream& bs );
		bool escribir_comestible( S_ptr<Comestible>& c, OutputBitStream& bs );

	public:
		/** Crea un paquete apto para deserializar. */
		PaqueteInit();

		/** Crea un paquete apto para serializar. */
		PaqueteInit( bool pacman, S_ptr<MapaBajoNivel> m );

		void serialize( OutputBitStream& bs );

		void deserialize( InputBitStream& bs );
	
		Operacion * get_operacion();
};

#endif /* _PAQUETEINIT_H__ */
