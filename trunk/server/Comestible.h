#ifndef __COMESTIBLE_H__
#define __COMESTIBLE_H__

#include "Personaje.h"

/** @brief Define una interfaz para todos los elementos del mapa que pueden ser
           comidos, por ejemplo, quesitos, power ups, frutitas, etcs.			
*/
class Comestible{
	private: 
		int puntaje;
	
	protected:
		Comestible(int puntos);			
	
	public:
		virtual ~Comestible();
	
		int get_puntos();
		
		virtual void afectar_personaje(Personaje& personaje)=0;	
		
	
		
};

#endif /*__COMESTIBLE_H__*/
