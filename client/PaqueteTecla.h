#ifndef __PAQUETETECLA_H__
#define __PAQUETETECLA_H__

#include "../common/PaqueteTeclaCommon.h"

class PaqueteTecla : public PaqueteTeclaCommon
{
   public:
		PaqueteTecla(int id_cliente);

		PaqueteTecla(int id_cliente,int flecha);

	   Operacion * get_operacion();

};

#endif /* __PAQUETETECLA_H__ */
