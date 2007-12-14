#ifndef __PAQUETEINIT_H__
#define __PAQUETEINIT_H__

#include "../common/PaqueteInitCommon.h"

class PaqueteInit : public PaqueteInitCommon
{
	public:
		/** Crea un paquete apto para deserializar. */
		PaqueteInit();

      PaqueteInit(bool pacman, S_ptr<MapaBajoNivel> m );

		Operacion * get_operacion();
};

#endif /* _PAQUETEINIT_H__ */
