//HEADER

#ifndef ITEM_NUEVO_H_
#define ITEM_NUEVO_H_

#include "item.h"
#include <editor/modelo.h>

/* CLASE ITEM NUEVO: Clase que representa el item "nuevo" para un menu.
   Hereda de item, implementa el ejecutar para realizar la accion correspondiente cuando se lo clikea. */

class ItemNuevo : public Item {

  public:

	//Constructor: Construye un item "nuevo" para un menu
	ItemNuevo();

	//Ejecutar: Ejecuta una accion al activar el item "nuevo"
	virtual void ejecutar(GtkWidget* widget, gpointer data);

};

#endif
