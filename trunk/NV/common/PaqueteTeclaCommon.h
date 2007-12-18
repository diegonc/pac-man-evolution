#ifndef __PAQUETETECLACOMMON_H__
#define __PAQUETETECLACOMMON_H__

#include "Paquete.h"


class PaqueteTeclaCommon : public Paquete
{
    protected:
		int id_cliente;
		
		int FlechaProt;
		
		static int flecha_map[4];
		
		int al_protocolo( int flecha );
		
		int desde_protocolo( int flecha );
	
	public:
		PaqueteTeclaCommon(int id_cliente);
		
		PaqueteTeclaCommon(int id_cliente,int flecha);
		
		virtual Operacion * get_operacion() = 0;
		
		void serialize( OutputBitStream& bs );
		
		void deserialize( InputBitStream& bs );
};

#endif /* __PAQUETETECLACOMMON_H__ */
