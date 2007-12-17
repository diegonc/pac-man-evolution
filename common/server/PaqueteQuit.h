#ifndef __PAQUETEQUIT_H__
#define __PAQUETEQUIT_H__

#include <server/Paquete.h>
//#include <server/MapaBajoNivel.h>

class PaqueteQuit: public Paquete
{
    public:
		PaqueteQuit();

		void serialize( OutputBitStream& bs );

		void deserialize( InputBitStream& bs );

		Operacion* get_operacion();
};

#endif /* __PAQUETEQUIT_H__ */
