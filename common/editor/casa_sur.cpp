//Header
#include <editor/casa_sur.h>

/* CLASE CASA SUR: Clase que representa una casa de fantasmas con orientacion SUR. Hereda de CasaFantasmas. */

/* Constructor: */

CasaSur::CasaSur (int pos_x, int pos_y) : CasaFantasmas(pos_x, pos_y, SUR ){
	for (int cont1 = 0; cont1 < this->get_alto(); cont1++)
		for (int cont2 = 0; cont2 < this->get_ancho(); cont2++)
			this->set_habitable(cont1, cont2, true);
	
	this->set_habitable(2,0,false);
	this->set_habitable(2,2,false);
	
	S_ptr<Punto> conec (new Punto(pos_x + this->get_alto(), pos_y + 1));
	this->set_posible_conexion(2,1, conec);
}

/* Get Ruta Imagen: */

char* CasaSur::get_ruta_imagen(){
		return RUTA_CASA_SUR;
}
