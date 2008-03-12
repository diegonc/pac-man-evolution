#ifndef __PAQUETESTATUS_H__
#define __PAQUETESTATUS_H__

#include <server/PaqueteStatusCommon.h>

class PaqueteStatus: public PaqueteStatusCommon{
	public:
	PaqueteStatus();

        ~PaqueteStatus();
	
	void deserialize( InputBitStream& bs );

        Operacion * get_operacion();
		
};

#endif /* __PAQUETESTATUS_H__ */
