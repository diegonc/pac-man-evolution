#ifndef __MUNDO_H__
#define __MUNDO_H__

#include "Mapa.h"

class Mundo
{
	public:	
		virtual Mapa& get_mapa_activo() = 0;
	
		virtual ~Mundo(){}
};

#endif /* __MUNDO_H__ */
