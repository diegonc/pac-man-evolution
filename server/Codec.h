#ifndef __CODEC_H__
#define __CODEC_H__

#include "Operacion.h"
#include "Paquete.h"
#include "../common/smart_pointer.h"

class Codec
{
	private:
		Codec();
		Codec(Codec& c);
		static S_ptr<Codec> instancia;
		
	public:
		static S_ptr<Codec> get_instancia();
		~Codec();
		Operacion* procesar( Paquete* pkt );
		Paquete* procesar( Operacion* op );
};

#endif /* __CODEC_H__ */
