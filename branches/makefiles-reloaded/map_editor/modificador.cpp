//Header
#include "modificador.h"

/* CLASE MODIFICADOR: Esta clase abstracta representa un elemento modificador y desciende de elemento.
   Todos los modificadores tienen un tamanio de 1 x 1 y su orientacion es nula. */

/* Constructor: */

Modificador::Modificador(int pos_x, int pos_y) : Elemento(pos_x, pos_y, 1, 1, NULA) {}

/* Es Estructural: */

bool Modificador::es_estructural(){
	return false;
}

/* Es Punto Conexion: */

bool Modificador::es_punto_conexion(int x, int y){
	return false;
}

/* Hay Conexion: */

bool Modificador::hay_conexion(int x1, int y1, int x2, int y2){
	return false;	
}

/* Es Habitable: */

bool Modificador::es_habitable(int x, int y){
	return false;
}

/* Agregate: */

bool Modificador::agregate(S_ptr<Elemento> instancia, Mapa* mapa){
	bool result = true;
	//Obtengo el casillero en las posiciones del elemento
	S_ptr<Casillero> casillero = mapa->get_casillero(this->get_pos_x(), this->get_pos_y());
	if (!casillero.es_nulo()){
		//Obtengo el estructural en ese casillero
		S_ptr<Elemento> estructural = casillero->get_estructural();
		//Si hay un estructural (que no es casa fantasma), no hay otro modif y el lugar es habitable lo agrego en el mapa
		if ((!casillero->tiene_modificador()) 
			&& (!estructural.es_nulo())
			&& (!(estructural->get_tipo() == CASA))
			&& (estructural->es_habitable(this->get_pos_x(), this->get_pos_y()))){
			mapa->insertar_elemento(instancia);
		} else
			result = false;	
	} else
		result = false;
	return result;
}
