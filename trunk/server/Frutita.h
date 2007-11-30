#ifndef __FRUTITA_H__
#define __FRUTITA_H__

#include "Comestible.h"

class Frutita : public Comestible{
	public:
		//TODO cambiar esto
		Frutita(Posicion &p):Comestible(10, p){}
		
		~Frutita(){}
		
		void afectar_personaje(Personaje& personaje){}
			
		Enum_Comestible get_tipo(){return Comestible::frutita;}
};

#endif /*__FRUTITA_H__*/
