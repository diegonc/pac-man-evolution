#ifndef __PAQUETEINIT_H__
#define __PAQUETEINIT_H__

#include "Paquete.h"
#include "Mapa.h"

class PaqueteInit : public Paquete
{
	private:
		/** @brief Determina si el cliente que recibe el paquete es el pacman o no.
		 */
		bool esPacman;

		/** @brief Mapa en el que se desarrolla el juego.
		 */
		Mapa& mapa;
		/* el atributo mapa deberia reemplazar a los que siguen. */

		/** @brief Ancho del grafo.
		 */
		int grafo_ancho;

		/** @brief Alto del grafo.
		 */
		int grafo_alto;

		char* grafo_aristas;

	public:
		PaqueteInit();

		void serialize( OutputBitStream& bs );

		void deserialize( InputBitStream& bs );
};

#endif /* _PAQUETEINIT_H__ */
