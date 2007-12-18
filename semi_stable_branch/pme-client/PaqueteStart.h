#ifndef __PAQUETESTART_H__
#define __PAQUETESTART_H__

#include "../common/PaqueteStartCommon.h"

class PaqueteStart: public PaqueteStartCommon
{
    public:
		/** Crea un paquete apto para deserializar. */
		PaqueteStart();

		/** Crea un paquete apto para serializar. */
		PaqueteStart(int id_cliente); 

		Operacion * get_operacion();
};

#endif /* __PAQUETESTART_H__ */
