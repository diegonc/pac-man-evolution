//Header
#include "casa_oeste.h"

/* CLASE CASA OESTE: Clase que representa una casa de fantasmas con orientacion OESTE. Hereda de CasaFantasmas. */

/* Constructor: */

CasaOeste::CasaOeste (int pos_x, int pos_y) : CasaFantasmas(pos_x, pos_y, OESTE ){
	for (int cont1 = 0; cont1 < this->get_alto(); cont1++)
		for (int cont2 = 0; cont2 < this->get_ancho(); cont2++)
			this->set_habitable(cont1, cont2, true);
	
	this->set_habitable(0,0,false);
	this->set_habitable(2,0,false);
	
	S_ptr<Punto> conec (new Punto(pos_x + 1, pos_y - 1));
	this->set_posible_conexion(1,0, conec);
}

/* Get Ruta Imagen: */

char* CasaOeste::get_ruta_imagen(){
		return RUTA_CASA_OESTE;
}

/* ///////////////TEMPORAL/////////////// */
char* CasaOeste::toString(){
	return "CASA OESTE";
}
