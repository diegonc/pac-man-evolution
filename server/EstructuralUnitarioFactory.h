#ifndef __ESTRUCTURAL_UNITARIO_FACTORY_H__
#define __ESTRUCTURAL_UNITARIO_FACTORY_H__

/**
*	@brief	Esta clase implementa, aplicando el facory method, una fabrica de 
*			EstructuralesUnitarios.
*/

#include "EstructuralUnitario.h"
#include "../common/smart_pointer.h"

class EstructuralUnitarioFactory{
	
	public:
		EstructuralUnitarioFactory(){}
		virtual ~EstructuralUnitarioFactory(){}
		/**
		*	@brief 	Metodo de construccion
		*
		*	@param p Posicion del estructural
		*	@param tipo_estructural Tipo del cual va a ser
		*	@param tipo_comestible Tipo del comestible que va a contener, si
		*		   se construye alguno que no acepta los mismos, se ignora
		*
		*	@return Smart pointer con el objeto creado
		*/
		virtual S_ptr<EstructuralUnitario> construir(Posicion &p,
				EstructuralUnitario::Enum_Estructural tipo_estructural, 
				Comestible::Enum_Comestible  tipo_comestible);
	
		
};

#endif /*__ESTRUCTURAL_UNITARIO_FACTORY_H__*/
