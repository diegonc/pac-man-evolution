#ifndef __QUESITO_H__
#define __QUESITO_H__

#include "Comestible.h"

#define PUNTOS_QUESO	1

class Quesito : public Comestible{
	public:
		Quesito():Comestible(PUNTOS_QUESO){}
		
		~Quesito(){}
		
		void afectar_personaje(Personaje& personaje){}
};

#endif /*__QUESITO_H__*/
