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

/* Es Habitable: */

bool Modificador::es_habitable(int x, int y){
	return false;
}

/* Agregate: */

bool Modificador::agregate(Mapa* mapa){
	bool result = true;
	S_ptr<Casillero> casillero = mapa->get_casillero(this->get_pos_x(), this->get_pos_y());
	if (!casillero.es_nulo()){
		S_ptr<Elemento> estructural = casillero->get_estructural();
		if ((!casillero->tiene_modificador()) && (!estructural.es_nulo()) && (estructural->es_habitable(this->get_pos_x(), this->get_pos_y()))){
			mapa->insertar_elemento(this);
		} else
			result = false;	
	} else
		result = false;
	return result;
}