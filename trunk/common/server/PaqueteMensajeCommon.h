#ifndef __PAQUETEMENSAJECOMMON_H__
#define __PAQUETEMENSAJECOMMON_H__

#include <server/Paquete.h>
#include <server/OperacionNula.h>
#include <string>

class PaqueteMensajeCommon: public Paquete
{
    protected:
        std::string Mensaje;
	
	public:
		PaqueteMensajeCommon();

		void serialize( OutputBitStream& bs );

		void deserialize( InputBitStream& bs );
	
		virtual Operacion * get_operacion();
};

#endif /* __PAQUETEMENSAJECOMMON_H__ */
