#ifndef __PAQUETESTATUSCOMMON_H__
#define __PAQUETESTATUSCOMMON_H__

#include "Paquete.h"
#include "math.h"
#include <list>
#include "Jugador.h"
#include "../common/smart_pointer.h"

//#include "MapaBajoNivel.h"

class PaqueteStatusCommon : public Paquete{
    protected:
        Operacion* Oper;
	
    public:
		PaqueteStatusCommon();

		virtual void serialize( OutputBitStream& bs );

		virtual void deserialize( InputBitStream& bs );

		virtual Operacion* get_operacion();
};

#endif /* __PAQUETESTATUS_H__ */
