//HEADER

#ifndef ITEM_GUARDAR_H_
#define ITEM_GUARDAR_H_

#include "item.h"
#include "gui.h"
#include "file_chooser.h"

/* CLASE ITEM GUARDAR: Clase que representa el item "guardar" para un menu.
   Hereda de item, implementa el ejecutar para realizar la accion correspondiente cuando se lo clikea. */

class ItemGuardar : public Item {

  public:

	//Constructor: Construye un item "guardar" para un menu
	ItemGuardar();

	//Ejecutar: Ejecuta una accion al activar el item "guardar"
	virtual void ejecutar(GtkWidget* widget, gpointer data);

};

#endif
