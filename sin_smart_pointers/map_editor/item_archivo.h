//HEADER

#ifndef ITEM_ARCHIVO_H_
#define ITEM_ARCHIVO_H_

#include "item.h"

/* CLASE ITEM ARCHIVO: Clase que representa el item "archivo" para el menu.
   Hereda de item, implementa el ejecutar para realizar la accion correspondiente cuando se lo clikea. */

class ItemArchivo : public Item {

  public:

	//Constructor: Construye un item "archivo" para un menu
	ItemArchivo();

	//Ejecutar: Ejecuta una accion al activar el item "archivo"
	virtual void ejecutar(GtkWidget* widget, gpointer data);

};

#endif
