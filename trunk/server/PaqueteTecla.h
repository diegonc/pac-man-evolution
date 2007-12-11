#ifndef __PAQUETETECLA_H__
#define __PAQUETETECLA_H__

#include "Paquete.h"
#include "KeyOp.h"
//#include "MapaBajoNivel.h"

class PaqueteTecla : public Paquete
{
    private:
	int id_cliente;
	int FlechaProt;
	
	public:
		PaqueteTecla(int id_cliente);

		PaqueteTecla(int id_cliente,int flecha);

	        Operacion * get_operacion();

		void serialize( OutputBitStream& bs );

		void deserialize( InputBitStream& bs );
};

#endif /* __PAQUETETECLA_H__ */
