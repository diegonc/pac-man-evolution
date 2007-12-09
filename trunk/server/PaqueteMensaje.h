#ifndef __PAQUETEMENSAJE_H__
#define __PAQUETEMENSAJE_H__

#include "Paquete.h"
//#include "MapaBajoNivel.h"
#include <string>

class PaqueteMensaje: public Paquete
{
    private:
        std::string Mensaje;
	
	public:
		PaqueteMensaje();

        std::string get_mensaje();

        void set_mensaje(std::string msg);

		void serialize( OutputBitStream& bs );

		void deserialize( InputBitStream& bs );
};

#endif /* __PAQUETEMENSAJE_H__ */
