#ifndef __PAQUETESTATUS_H__
#define __PAQUETESTATUS_H__

#include "Paquete.h"
#include <list>
#include "ModeloServidor.h"
#include "Jugador.h"
#include "../common/smart_pointer.h"

//#include "MapaBajoNivel.h"

class PaqueteStatus: public Paquete
{
    private:
        ModeloServidor* Model;
    public:
		PaqueteStatus();

		ModeloServidor* get_modelo(){
                return Model;
        }

        void set_modelo(ModeloServidor* modelo){
                Model=modelo;
        }

		void serialize( OutputBitStream& bs );

		void deserialize( InputBitStream& bs );
};

#endif /* __PAQUETESTATUS_H__ */
