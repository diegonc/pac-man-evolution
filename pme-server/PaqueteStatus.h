#ifndef __PAQUETESTATUS_H__
#define __PAQUETESTATUS_H__

#include <server/PaqueteStatusCommon.h>

class PaqueteStatus: public PaqueteStatusCommon{
	public:
	PaqueteStatus(std::list<NovedadComestible>* Novedad,
			S_ptr<ModeloCommon> modelo);

	PaqueteStatus();

      ~PaqueteStatus();

      Operacion * get_operacion();
      
		
};

#endif /* __PAQUETESTATUS_H__ */
