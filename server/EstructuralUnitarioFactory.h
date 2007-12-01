#ifndef __ESTRUCTURAL_UNITARIO_FACTORY_H__
#define __ESTRUCTURAL_UNITARIO_FACTORY_H__

#include "EstructuralUnitario.h"
#include "../common/smart_pointer.h"

class EstructuralUnitarioFactory{
	
	public:
		virtual S_ptr<EstructuralUnitario> construir(Posicion &p,
				EstructuralUnitario::Enum_Estructural tipo_estructural, 
				Comestible::Enum_Comestible  tipo_comestible);
	
		virtual ~EstructuralUnitarioFactory(){}
};

#endif /*__ESTRUCTURAL_UNITARIO_FACTORY_H__*/
