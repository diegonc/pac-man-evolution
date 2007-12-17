#ifndef __PAQUETESTOP_H__
#define __PAQUETESTOP_H__

#include <server/Paquete.h>

class PaqueteStop : public Paquete
{
	private:
		char razon;
		int puntuacion;
		/*
		 * Estadisticas ?
		 */

	public:
      
      static const char pacman_gano;
		static const char pacman_comido;
		static const char pacman_desconecto;
		static const char cant_insuficiente;
		static const char termino_juego;
      
		/** Construye un paquete apto para deserializar. */
		PaqueteStop();

		/** Construye un paquete apto para serializar. */
		PaqueteStop(const char razon, int puntaje);

		void serialize( OutputBitStream& bs );

		void deserialize( InputBitStream& bs );
	
		Operacion * get_operacion();
};

#endif
