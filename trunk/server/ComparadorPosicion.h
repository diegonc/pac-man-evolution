#ifndef __COMPARADOR_POSICION_H__
#define __COMPARADOR_POSICION_H__

#include <iostream>
	
class ComparadorPosicion{
	
	public:
		bool operator()(const Posicion &e1, const Posicion &e2){
			if( ( (int)e1.get_x() == (int)e2.get_x() ) && ((int)e1.get_y() == (int)e2.get_y()) )
				return true;
			else
				return false;
			
		}
};

#endif /*__COMPARADOR_POSICION_H__*/
