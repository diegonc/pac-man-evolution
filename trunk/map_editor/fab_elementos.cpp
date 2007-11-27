//Header
#include "fab_elementos.h"

/* CLASE FABRICA ELEMENTOS: Clase que se encarga de encapsular la creacion de elementos de cualquier tipo (modificadores
o estructurales). */

/* Construir: */

S_ptr<Elemento> Fab_Elementos::construir (TipoElem tipo, int pos_x, int pos_y, Orientacion orientacion){
	S_ptr<Elemento> elemento;
	switch (tipo) {
		case PASILLO:
			elemento = construir_pasillo(pos_x, pos_y, orientacion);
			break;
	}
	return elemento;
}

/* Construir Pasillo: */

S_ptr<Elemento> Fab_Elementos::construir_pasillo (int pos_x, int pos_y, Orientacion orientacion){
	S_ptr<Elemento> elemento;
	switch (orientacion) {
		case ESTE:
		case OESTE: {
			S_ptr<Elemento> pas_horiz (new PasilloHoriz(pos_x, pos_y));
			elemento = pas_horiz;
			break;
			}
		case NORTE:
		case SUR: {
			S_ptr<Elemento> pas_vert (new PasilloVert(pos_x, pos_y));
			elemento = pas_vert;
			break;
			}
	}
	return elemento;
}
