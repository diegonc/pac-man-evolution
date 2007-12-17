#include <server/EstructuralUnitarioFactory.h>

#include <server/EstructuralPasillo.h>
#include <server/EstructuralCasaFantasma.h>

S_ptr<EstructuralUnitario> EstructuralUnitarioFactory::construir(Posicion &p,
				EstructuralUnitario::Enum_Estructural tipo_estructural, 
				Comestible::Enum_Comestible  tipo_comestible){
	
	S_ptr<EstructuralUnitario> e;
	//implementado con un switch
	switch( tipo_estructural ){
		
		case _CASA_FANTASMA: 
			e = S_ptr<EstructuralUnitario>(new EstructuralCasaFantasma(p));
			return e;
			break;
		case _PASILLO:
			e = S_ptr<EstructuralUnitario>(new EstructuralPasillo(tipo_comestible, p));
			return e;
			break;
		default:
			return e; //devuelve uno nulo en caso de no haber podido ser creado
			
	}
					
}
