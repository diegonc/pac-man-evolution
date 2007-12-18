#ifndef __PAQUETEMENSAJE_H__
#define __PAQUETEMENSAJE_H__

#include <server/PaqueteMensajeCommon.h>
#include "OperacionMensaje.h"


class PaqueteMensaje: public PaqueteMensajeCommon
{
	public:
	PaqueteMensaje();
	PaqueteMensaje(std::string Mensaje);
	virtual Operacion * get_operacion();
};

#endif /* __PAQUETEMENSAJE_H__ */
