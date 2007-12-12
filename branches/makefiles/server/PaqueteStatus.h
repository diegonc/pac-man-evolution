#ifndef __PAQUETESTATUS_H__
#define __PAQUETESTATUS_H__

#include "Paquete.h"
#include "math.h"
#include <list>
#include "ModeloServidor.h"
#include "OperacionStatus.h"
#include "Jugador.h"
#include "../common/smart_pointer.h"

//#include "MapaBajoNivel.h"

class PaqueteStatus: public Paquete
{
    private:
        OperacionStatus* Oper;
	
    public:
		PaqueteStatus();

		void serialize( OutputBitStream& bs );

		void deserialize( InputBitStream& bs );

		Operacion* get_operacion();
};

#endif /* __PAQUETESTATUS_H__ */
