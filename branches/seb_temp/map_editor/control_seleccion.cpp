//Header
#include "control_seleccion.h"

/* CLASE CONTROL SELECCION: Clase singleton que se encarga de controlar cual es el ultimo item
   que ha sido seleccionado en cualquiera de los paneles de elementos. */

ControlSeleccion* ControlSeleccion::instancia = NULL;

/* Constructor Privado: */

ControlSeleccion::ControlSeleccion(){
	S_ptr<ItemElem> elem_nulo;
	this->item_seleccionado = elem_nulo;
}

/* Destructor Privado: */

ControlSeleccion::~ControlSeleccion(){}

/* Get Instance: */

ControlSeleccion* ControlSeleccion::get_instance(){
	if (instancia == NULL){
		instancia = new ControlSeleccion();
		return instancia;
	}
	else
		return instancia;
}

/* Get Tipo Selec: */

TipoElem ControlSeleccion::get_tipo_selec(){
	if (!this->item_seleccionado.es_nulo())
		return this->item_seleccionado->get_tipo();
	else
		return PASILLO;
}

/* Get Orientacion Selec: */

Orientacion ControlSeleccion::get_orientacion_selec(){
	if (!this->item_seleccionado.es_nulo())
		return this->item_seleccionado->get_orientacion();
	else
		return ESTE;
}

/* Actualizar:  */

void ControlSeleccion::actualizar(Observable * observable, void * param){
	S_ptr<ItemElem> item = *((S_ptr<ItemElem>*) param);
	this->item_seleccionado = item;
}

/* Destroy: */

void ControlSeleccion::destroy(){
	delete (instancia);
}
