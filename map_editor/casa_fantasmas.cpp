//Header
#include "casa_fantasmas.h"

/* CLASE CASA FANTASMA: Clase que representa una casa de fantasmas en una orientacion determinada. Hereda de estructural. */

/* Constructor: */

CasaFantasmas::CasaFantasmas(int pos_x, int pos_y, Orientacion orientacion) : Estructural(pos_x, pos_y, CASA_ANCHO, CASA_ALTO, orientacion) {

}

/* Agregate: */

bool CasaFantasmas::agregate(S_ptr<Elemento> instancia, Mapa* mapa){
	bool resultado;
	if (!mapa->tiene_casa_fantasmas()){
		resultado = Estructural::agregate(instancia, mapa);
		if (resultado)
			mapa->set_casa_fantasmas(true);
	} else
		resultado = false;
	return resultado;
}

/* Quitate: */

void CasaFantasmas::quitate(S_ptr<Elemento> instancia, Mapa* mapa){
	Elemento::quitate(instancia, mapa);
	mapa->set_casa_fantasmas(false);
}

/* Get Tipo: */

TipoElem CasaFantasmas::get_tipo(){
	return CASA;
}
