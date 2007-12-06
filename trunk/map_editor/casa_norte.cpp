//Header
#include "casa_norte.h"

/* CLASE CASA NORTE: Clase que representa una casa de fantasmas con orientacion NORTE. Hereda de CasaFantasmas. */

/* Constructor: */

CasaNorte::CasaNorte (int pos_x, int pos_y) : CasaFantasmas(pos_x, pos_y, NORTE ){
	for (int cont1 = 0; cont1 < this->get_alto(); cont1++)
		for (int cont2 = 0; cont2 < this->get_ancho(); cont2++)
			this->set_habitable(cont1, cont2, true);
	
	this->set_habitable(0,0,false);
	this->set_habitable(0,2,false);
	
	S_ptr<Punto> conec (new Punto(pos_x - 1, pos_y + 1));
	this->set_posible_conexion(0,1, conec);
}

/* Get Ruta Imagen: */

char* CasaNorte::get_ruta_imagen(){
		return RUTA_CASA_NORTE;
}

/* ///////////////TEMPORAL/////////////// */
char* CasaNorte::toString(){
	return "CASA NORTE";
}
