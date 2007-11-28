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
		
		static const char power_up;
		static const char quesito;
		static const char frutita;
		
		typedef const char Enum_Comestible;
		
		virtual ~Comestible();
	
		int get_puntos();
		
		virtual void afectar_personaje(Personaje& personaje)=0;	
	
		virtual Enum_Comestible get_tipo()=0;
		
	
		
};

#endif /*__COMESTIBLE_H__*/
