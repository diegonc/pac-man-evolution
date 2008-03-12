//HEADER
#include "item_elem.h"

/* CLASE ITEM ELEM: Clase que simboliza un item para un panel de elementos. Contiene
   un tipo, una orientacion y una ruta para su imagen. */

//Constructor:

ItemElem::ItemElem(TipoElem tipo, Orientacion orientacion, char* ruta_imagen){
	this->tipo = tipo;
	this->orientacion = orientacion;
	this->ruta = ruta_imagen;
}

//Get Tipo:

TipoElem ItemElem::get_tipo() const{
	return this->tipo;
}

//Get Orientacion:

Orientacion ItemElem::get_orientacion() const{
	return this->orientacion;
}

//Get Ruta Imagen:

char* ItemElem::get_ruta_imagen() const{
	return this->ruta;
}
