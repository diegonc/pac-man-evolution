#ifndef __MUNDO_H__
#define __MUNDO_H__

#include "Mapa.h"

class Mundo
{
	private:
		Mundo();
		~Mundo();

	public:	
		Mapa* get_mapa_activo() = 0;
};

#endif /* __MUNDO_H__ */
