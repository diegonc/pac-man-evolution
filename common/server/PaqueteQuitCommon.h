#ifndef __PAQUETEQUITCOMMON_H__
#define __PAQUETEQUITCOMMON_H__

#include <server/Paquete.h>

class PaqueteQuitCommon: public Paquete
{
    public:
		PaqueteQuitCommon();

		void serialize( OutputBitStream& bs );

		void deserialize( InputBitStream& bs );

	   virtual Operacion * get_operacion()=0;
};

#endif /* __PAQUETEQUIT_H__ */
