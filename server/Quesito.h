#ifndef __QUESITO_H__
#define __QUESITO_H__

#include "Comestible.h"

#define PUNTOS_QUESO	1

class Quesito : public Comestible{
	public:
		Quesito(Posicion &p):Comestible(PUNTOS_QUESO, p){}
		
		~Quesito(){}
		
		void afectar_personaje(Personaje& personaje){}
			
		Enum_Comestible get_tipo(){return Comestible::quesito;}
};

#endif /*__QUESITO_H__*/
