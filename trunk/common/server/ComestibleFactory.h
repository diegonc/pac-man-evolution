#ifndef __COMESTIBLE_FACTORY_H__
#define __COMESTIBLE_FACTORY_H__

/**
*	@brief	Esta clase implementa el patron factory method y permite la creacion
*			de comestibles
*/			

#include <server/Comestible.h>

class ComestibleFactory{
	
	private:
	
		ComestibleFactory(ComestibleFactory &c);
	
	public:
		/**
		*	@brief Constructor de la clase
		*/	
		ComestibleFactory();
	
		/**
		*	@brief Destructor de la clase
		*/
		~ComestibleFactory();
		
		/**
		*	@brief Metodo para la construccion de comestibles
		*
		*	@param tipo Tipo de comestible que se desea construir
		*	@param p	Posicion donde se va a ubicar el comestible
		*
		*	@return Comestible creado y en caso de error, NULL
		*/		
		Comestible * construir(Comestible::Enum_Comestible tipo, Posicion &p);
		
		
};

#endif /*__COMESTIBLE_FACTORY_H__*/
