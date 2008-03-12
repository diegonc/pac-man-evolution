#ifndef __COMPARADOR_POSICION_H__
#define __COMPARADOR_POSICION_H__

/**
*	@brief 	Esta clase implementa un comparador de objetos Posicion. 
*			Para hacerlo, redondea para abajo los valores de las coordenadas.
*
*/
#include <math.h>
#include <iostream>
	
class ComparadorPosicion{
	
	public:
		/**
		*	@brief Define el operador () que es usado para comparar, por ej:
		*			Comp c; c(p1, p2) => asi se puede comparar
		*/
		bool operator()(const Posicion &e1, const Posicion &e2){
						
			if( ( floor(e1.get_x()) == floor(e2.get_x()) ) && (floor(e1.get_y()) == floor(e2.get_y())) )
				return true;
			else
				return false;
			
		}
};

#endif /*__COMPARADOR_POSICION_H__*/
