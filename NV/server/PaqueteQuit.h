#ifndef __PAQUETEQUIT_H__
#define __PAQUETEQUIT_H__

#include "../common/PaqueteQuitCommon.h"

class PaqueteQuit : public PaqueteQuitCommon
{
	public:
		/** Crea un paquete apto para deserializar. */
		PaqueteQuit();

		Operacion * get_operacion();
};

#endif /* _PAQUETEQUIT_H__ */
