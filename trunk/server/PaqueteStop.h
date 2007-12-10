#ifndef __PAQUETESTOP_H__
#define __PAQUETESTOP_H__

#include "Paquete.h"
#include "Operacion.h"

class PaqueteStop : public Paquete
{
	private:
		int razon;
		int puntuacion;
		/*
		 * Estadisticas ?
		 */

	public:
		/** Construye un paquete apto para deserializar. */
		PaqueteStop();

		/** Construye un paquete apto para serializar. */
		PaqueteStop(int razon, int puntaje);

		void serialize( OutputBitStream& bs );

		void deserialize( InputBitStream& bs );
	
		Operacion * get_operacion();
};

#endif
