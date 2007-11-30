#ifndef __MUNDO_H__
#define __MUNDO_H__

#include "MapaBajoNivel.h"

class MundoBajoNivel
{
	public:	
		virtual MapaBajoNivel& get_mapa_activo() = 0;
	
		virtual ~MundoBajoNivel(){}
};

#endif /* __MUNDO_H__ */
