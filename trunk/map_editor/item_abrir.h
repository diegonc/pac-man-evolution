//HEADER

#ifndef ITEM_ABRIR_H_
#define ITEM_ABRIR_H_

#include "item.h"

/* CLASE ITEM ABRIR: Clase que representa el item "abrir" para un menu.
   Hereda de item, implementa el ejecutar para realizar la accion correspondiente cuando se lo clikea. */

class ItemAbrir : public Item {

  public:

	//Constructor: Construye un item "abrir" para un menu
	ItemAbrir();

	//Ejecutar: Ejecuta una accion al activar el item "abrir"
	virtual void ejecutar(GtkWidget* widget, gpointer data);

};

#endif
