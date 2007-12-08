#ifndef __PAQUETEMENSAJE_H__
#define __PAQUETEMENSAJE_H__

#include "Paquete.h"
//#include "MapaBajoNivel.h"

class PaqueteMensaje: public Paquete
{
    private:
        string Mensaje;
	public:
		PaqueteMensaje();

        string get_mensaje();

        void set_mensaje(string msg);

		void serialize( OutputBitStream& bs );

		void deserialize( InputBitStream& bs );
};

#endif /* __PAQUETEMENSAJE_H__ */
