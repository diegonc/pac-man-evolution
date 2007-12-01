#include "EstructuralUnitarioFactory.h"

#include "EstructuralPasillo.h"
#include "EstructuralCasaFantasma.h"
#include "EstructuralSalidaPacman.h"

S_ptr<EstructuralUnitario> EstructuralUnitarioFactory::construir(Posicion &p,
				EstructuralUnitario::Enum_Estructural tipo_estructural, 
				Comestible::Enum_Comestible  tipo_comestible){
	S_ptr<EstructuralUnitario> e;
	switch( tipo_estructural ){
		
		case CASA_FANTASMA: 
			e = S_ptr<EstructuralUnitario>(new EstructuralCasaFantasma(p));
			return e;
			break;
		case PASILLO:
			e = S_ptr<EstructuralUnitario>(new EstructuralPasillo(tipo_comestible, p));
			return e;
			break;
			
		case SALIDA_PACMAN:
			e = S_ptr<EstructuralUnitario>(new EstructuralSalidaPacman(p));	
			return e;
			break;
		default:
			return e;
			
	}
					
}
