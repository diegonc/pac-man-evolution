#ifndef __PAQUETESTOP_H__
#define __PAQUETESTOP_H__

#include "../common/PaqueteStopCommon.h"

class PaqueteStop : public PaqueteStopCommon
{
	public:
		/** Crea un paquete apto para deserializar. */
		PaqueteStop();
		
		PaqueteStop( char Razon, int Puntuacion);

		Operacion * get_operacion();
};

#endif /* _PAQUETESTOP_H__ */
