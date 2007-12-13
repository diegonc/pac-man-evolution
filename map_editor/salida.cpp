//Header
#include "salida.h"

/* CLASE SALIDA: Clase que representa la salida del PacMan. Desciende de modificador. Ocupa un casillero. */

/* Constructor: */

Salida::Salida (int pos_x, int pos_y) : Modificador(pos_x, pos_y) {}

/* Get Tipo: */
	
TipoElem Salida::get_tipo(){
	return SALIDA;	
}

/* Get Ruta Imagen: */

char* Salida::get_ruta_imagen(){
		return RUTA_SALIDA;
}

/* Agregate: */

bool Salida::agregate(S_ptr<Elemento> instancia, Mapa* mapa){
	bool resultado;
	if (!mapa->tiene_salida()){
		resultado = Modificador::agregate(instancia, mapa);
		if (resultado)
			mapa->set_salida(true);
	} else
		resultado = false;
	return resultado;
}

/* Quitate: */

void Salida::quitate(S_ptr<Elemento> instancia, Mapa* mapa){
	Elemento::quitate(instancia, mapa);
	mapa->set_salida(false);
}
