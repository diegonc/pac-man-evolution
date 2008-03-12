#ifndef __PAQUETESTATUSCOMMON_H__
#define __PAQUETESTATUSCOMMON_H__

#include "Paquete.h"
#include "math.h"
#include <list>
#include "../common/NovedadComestible.h"
#include "Jugador.h"
#include "../common/smart_pointer.h"
#include "../common/ModeloCommon.h"

//#include "MapaBajoNivel.h"

class PaqueteStatusCommon : public Paquete{
    protected:
        Operacion* Oper;
	std::list<NovedadComestible> Novedades;
	std::list<Jugador*> jugadores;
	unsigned int ancho;
	unsigned int alto;
	
    public:
		PaqueteStatusCommon();

		PaqueteStatusCommon(std::list<NovedadComestible>* Novedades,
				S_ptr<ModeloCommon> modelo);

		virtual void serialize( OutputBitStream& bs );

		virtual void deserialize( InputBitStream& bs );

		virtual Operacion* get_operacion();
};

#endif /* __PAQUETESTATUS_H__ */
