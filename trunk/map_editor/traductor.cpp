//Header
#include "traductor.h"

/* CLASE TRADUCTOR: Clase que se encarga de traducir un mundo de alto nivel (del editor),
   a un mundo de bajo nivel (para el servidor). */

/* Traducir: */

MundoBajoNivel* Traductor::traducir(Mundo* mundo){
	MundoBajoNivel* mundo_bajo_nivel = new MundoBasicImp();
	for (unsigned int cont = 0; cont < mundo->get_cant_niveles(); cont++){
		S_ptr<Nivel> nivel = mundo->get_nivel(cont+1);
		S_ptr<MapaBajoNivel> mapa_bajo_nivel = this->traducir_mapa(nivel->get_mapa());
		mundo_bajo_nivel->agregar_mapa(mapa_bajo_nivel);
	}
	return mundo_bajo_nivel;
}

/* Traducir Mapa: */

S_ptr<MapaBajoNivel> Traductor::traducir_mapa (Mapa* mapa){
	S_ptr<MapaBajoNivel> mapa_bajo_nivel (new MapaImpSet(mapa->get_ancho(),mapa->get_alto()));
	for (unsigned int cont1 = 0; cont1 < mapa->get_alto(); cont1++)
		for (unsigned int cont2 = 0; cont2 < mapa->get_ancho(); cont2++){
			S_ptr<Casillero> casillero = mapa->get_casillero(cont1, cont2);
			S_ptr<Estructural> estructural = casillero->get_estructural();
			S_ptr<Modificador> modificador = casillero->get_modificador();
			Posicion pos(cont2, cont1);
			S_ptr<EstructuralUnitario>  estruct_bajo_nivel;
			if (!estructural.es_nulo())
				if (!modificador.es_nulo()){
					Comestible::Enum_Comestible  tipoComestible = this->trad_cod_elemento;
					
				}
					
			
			
		}
}

/* Trad Cod Elemento: */

const char Traductor::trad_cod_elemento(TipoElem tipo){
	
}
