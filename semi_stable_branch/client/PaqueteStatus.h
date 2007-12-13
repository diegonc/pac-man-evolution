#ifndef __PAQUETESTATUS_H__
#define __PAQUETESTATUS_H__

#include "../common/PaqueteStatusCommon.h"

class PaqueteStatus: public PaqueteStatusCommon{
	public:
		PaqueteStatus();

      ~PaqueteStatus();
	
		void deserialize( InputBitStream& bs );
		
};

#endif /* __PAQUETESTATUS_H__ */
