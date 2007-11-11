#ifndef __PERSONAJE_H__
#define __PERSONAJE_H__

#include "Direccion.h"

class Personaje
{
	private:
		Direccion dir;
	
	public:
		Direccion get_direccion() { return dir; }
};

#endif /* __PERSONAJE_H__ */
