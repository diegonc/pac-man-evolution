#ifndef __COMPARADOR_POSICION_H__
#define __COMPARADOR_POSICION_H__

#include <math.h>
#include <iostream>
	
class ComparadorPosicion{
	
	public:
		bool operator()(const Posicion &e1, const Posicion &e2){
						
			if( ( floor(e1.get_x()) == floor(e2.get_x()) ) && (floor(e1.get_y()) == floor(e2.get_y())) )
				return true;
			else
				return false;
			
		}
};

#endif /*__COMPARADOR_POSICION_H__*/
