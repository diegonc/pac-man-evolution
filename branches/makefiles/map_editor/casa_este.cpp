//Header
#include "casa_este.h"

/* CLASE CASA ESTE: Clase que representa una casa de fantasmas con orientacion ESTE. Hereda de CasaFantasmas. */

/* Constructor: */

CasaEste::CasaEste (int pos_x, int pos_y) : CasaFantasmas(pos_x, pos_y, ESTE ){
	for (int cont1 = 0; cont1 < this->get_alto(); cont1++)
		for (int cont2 = 0; cont2 < this->get_ancho(); cont2++)
			this->set_habitable(cont1, cont2, true);
	
	this->set_habitable(0,2,false);
	this->set_habitable(2,2,false);
	
	S_ptr<Punto> conec (new Punto(pos_x + 1, pos_y + this->get_ancho()));
	this->set_posible_conexion(1,2, conec);
}

/* Get Ruta Imagen: */

char* CasaEste::get_ruta_imagen(){
		return RUTA_CASA_ESTE;
}

/* ///////////////TEMPORAL/////////////// */
char* CasaEste::toString(){
	return "CASA ESTE";
}
