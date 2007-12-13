#ifndef __PAQUETESTATUS_H__
#define __PAQUETESTATUS_H__

#include "../common/PaqueteStatusCommon.h"

class PaqueteStatus: public PaqueteStatusCommon{
	public:
		PaqueteStatus();

      ~PaqueteStatus();

      Operacion * get_operacion();
      
		
};

#endif /* __PAQUETESTATUS_H__ */
