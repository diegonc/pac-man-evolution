#ifndef __PAQUETETECLA_H__
#define __PAQUETETECLA_H__

#include <server/PaqueteTeclaCommon.h>


class PaqueteTecla : public PaqueteTeclaCommon
{
 	public:
		PaqueteTecla(unsigned int id_cliente);

		PaqueteTecla(unsigned int id_cliente,int flecha);

	    Operacion * get_operacion();


		
};

#endif /* __PAQUETETECLA_H__ */
