#ifndef __PAQUETETECLA_H__
#define __PAQUETETECLA_H__

#include "Paquete.h"
#include "KeyOp.h"
//#include "MapaBajoNivel.h"

class PaqueteTecla : public Paquete
{
    private:
        KeyOp* OperacionTecla;
	int id_cliente;
	
	public:
		PaqueteTecla(int id_cliente);

        Operacion * get_operacion();

        void set_KeyOp(KeyOp* OperTecla);

		void serialize( OutputBitStream& bs );

		void deserialize( InputBitStream& bs );
};

#endif /* __PAQUETETECLA_H__ */
