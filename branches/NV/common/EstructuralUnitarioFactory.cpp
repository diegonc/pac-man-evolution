#include "EstructuralUnitarioFactory.h"

#include "EstructuralPasillo.h"
#include "EstructuralCasaFantasma.h"

EstructuralUnitario * EstructuralUnitarioFactory::construir(Posicion &p,
				EstructuralUnitario::Enum_Estructural tipo_estructural, 
				Comestible::Enum_Comestible  tipo_comestible){
	
	EstructuralUnitario * e = NULL;
	//implementado con un switch
	switch( tipo_estructural ){
		
		case _CASA_FANTASMA: 
			e = new EstructuralCasaFantasma(p);
			break;
		case _PASILLO:
			e = new EstructuralPasillo(tipo_comestible, p);
			break;
		default:
			break;
	}
	return e;
					
}
