#ifndef __POSICION_H__
#define __POSICION_H__

/**
*	@brief Esta clase representa una posicion en dos dimensiones (x,y)
*/

#include <server/Direccion.h>

typedef double Tipo_Coordenada;

class Posicion{
	
	
	private:
		Tipo_Coordenada x;
		Tipo_Coordenada y;
	public:
		/**
		*	@brief	Comstructor de la clase
		*	@param	x Coordenada x, por defecto toma 0
		*	@param	y Coordenada y, por defecto toma 0
		*/
		Posicion(Tipo_Coordenada x = 0.0, Tipo_Coordenada y = 0.0);
		
		/**
		*	@brief 	Constructor de copia
		*/
		Posicion( const Posicion &p);
		
		/**
		*	@brief 	Permite obtener el valor de la coordenada x
		*
		*	@return	Coordenada x de la posicion
		*/
		Tipo_Coordenada get_x() const;
			
		/**
		*	@brief 	Permite setter el valor de la coordenada x
		*
		*	@param 	x_nuevo Coordenada x de la posicion
		*/
		void set_x(Tipo_Coordenada x_nuevo);
		
		/**
		*	@brief 	Permite obtener el valor de la coordenada y
		*
		*	@return	Coordenada y de la posicion
		*/		
		Tipo_Coordenada get_y() const;
		
		/**
		*	@brief 	Permite setter el valor de la coordenada y
		*
		*	@param 	y_nuevo Coordenada x de la posicion
		*/
		void set_y(Tipo_Coordenada y_nuevo);
	
		/**
		*	@brief 	Este metodo incrementa una cantidad dada la posicion en
		*			la direccion pasada por parametro
		*
		*	@param 	cantidad Cantidad a incrementar
		*
		*	@param	direccion Direccion en la cual se incrementa
		*/
		void incrementar(Tipo_Coordenada cantidad, Direccion &direccion);
		
		/**
		*	@brief	Redefinicion del operador para comparar posiciones
		*/
		bool operator==(const Posicion &p);
		
		//Provisorio para control, despues sacar
		friend std::ostream& operator <<( std::ostream& os, const Posicion &p) 
     	{ 
         	os << "(" << p.get_x() << "," << p.get_y() << ")"; 
         	return os; 
     	} 
};
#endif /*__POSICION_H__*/
