#ifndef __PAQUETESTART_H__
#define __PAQUETESTART_H__

#include "Paquete.h"
#include <list>
#include "ModeloServidor.h"
#include "Jugador.h"
#include "../common/smart_pointer.h"

//#include "MapaBajoNivel.h"

class PaqueteStart: public Paquete
{
    private:
        int id_cliente; //TODO: REVISEN ESTO QUE HICE PORQUE NO ME SIRVE PARA UN BROADCAST
	
    public:
		/** Crea un paquete apto para deserializar. */
		PaqueteStart();

		/** Crea un paquete apto para serializar. */
		PaqueteStart(int id_cliente); //TODO: REVISEN ESTO QUE HICE PORQUE NO ME SIRVE PARA UN BROADCAST

		void serialize( OutputBitStream& bs );

		void deserialize( InputBitStream& bs );
	
		Operacion * get_operacion();
};

#endif /* __PAQUETESTART_H__ */
