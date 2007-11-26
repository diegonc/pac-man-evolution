#ifndef __PAQUETEINIT_H__
#define __PAQUETEINIT_H__

#include "Paquete.h"

class PaqueteInit : public Paquete
{
	private:
		/** @brief Determina si el cliente que recibe el paquete es el pacman o no.
		 */
		bool esPacman;

		/** @brief Ancho del grafo.
		 */
		int grafo_ancho;

		/** @brief Alto del grafo.
		 */
		int grafo_alto;

		char* grafo_aristas;

	public:
		PaqueteInit();

		void deserialize( BitStream& bs );
};

#endif /* _PAQUETEINIT_H__ */
