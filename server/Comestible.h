#ifndef __COMESTIBLE_H__
#define __COMESTIBLE_H__


/** @brief Define una interfaz para todos los elementos del mapa que pueden ser
           comidos, por ejemplo, quesitos, power ups, frutitas, etcs.			
*/


class Comestible{
	
	public:
		virtual ~Comestible(){}
	
		virtual void comer()=0;
}

#endif /*__COMESTIBLE_H__*/
