#ifndef __PAQUETESTARTCOMMON_H__
#define __PAQUETESTARTCOMMON_H__

#include <server/Paquete.h>

class PaqueteStartCommon: public Paquete
{
    protected:
        int id_cliente; 
	
    public:
		/** Crea un paquete apto para deserializar. */
		PaqueteStartCommon();

		/** Crea un paquete apto para serializar. */
		PaqueteStartCommon(int id_cliente); 

		void serialize( OutputBitStream& bs );

		void deserialize( InputBitStream& bs );
	
		Operacion * get_operacion() = 0;
};

#endif /* __PAQUETESTARTCOMMON_H__ */
