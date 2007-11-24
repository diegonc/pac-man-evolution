#ifndef __CASILLERO_H__
#define __CASILLERO_H__


#include "Comestible.h"
#include "../common/smart_pointer.h"
#include "Jugador.h"

class Casillero{
		
	private:
	
		Casillero(&Casillero c);
	public:
		
		Casillero();	
	
		virtual ~Casillero(){}
	
		virtual void ingresar(Jugador *jugador) = 0;

	
}
#endif /*__CASILLERO_H__*/
