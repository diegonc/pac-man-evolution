#ifndef __CODEC_H__
#define __CODEC_H__

#include "Operacion.h"
#include "Paquete.h"

class Codec
{
	public:
		Operacion* procesar( Paquete* pkt );
		Paquete* procesar( Operacion* op );
};

#endif /* __CODEC_H__ */
