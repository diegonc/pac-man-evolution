//HEADER

#ifndef ITEM_SALIR_H_
#define ITEM_SALIR_H_

#include "item.h"
#include "gui.h"

/* CLASE ITEM SALIR: Clase que representa el item "salir" para un menu.
   Hereda de item, implementa el ejecutar para realizar la accion correspondiente cuando se lo clikea. */

class ItemSalir : public Item {

  public:

	//Constructor: Construye un item "salir" para un menu
	ItemSalir();

	//Ejecutar: Ejecuta una accion al activar el item "salir"
	virtual void ejecutar(GtkWidget* widget, gpointer data);

};

#endif
