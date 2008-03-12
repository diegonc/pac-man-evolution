#ifndef __PAQUETESTOPCOMMON_H__
#define __PAQUETESTOPCOMMON_H__

#include "Paquete.h"

#define RazonPacmanGano 		0
#define RazonPacmanComido 		1
#define RazonPacmanDesconecto 		2
#define RazonCantidadInsuficiente 	3
#define RazonTerminoJuego 		4


class PaqueteStopCommon : public Paquete
{
	protected:
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
		PaqueteStopCommon();

		/** Construye un paquete apto para serializar. */
		PaqueteStopCommon(const char razon, int puntaje);

		void serialize( OutputBitStream& bs );

		void deserialize( InputBitStream& bs );
	
		virtual Operacion * get_operacion()=0;
};

#endif
