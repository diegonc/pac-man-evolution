//HEADER

#include "item_nuevo.h"

/* CLASE ITEM NUEVO: Clase que representa el item "nuevo" para un menu.
   Hereda de item, implementa el ejecutar para realizar la accion correspondiente cuando se lo clikea. */

//Constructor:

ItemNuevo::ItemNuevo() : Item(N_NUEVO){}

//Ejecutar:

void ItemNuevo::ejecutar(GtkWidget* widget, gpointer data){
	Mundo* mundo_nuevo = new Mundo();
	Modelo::get_instance()->set_mundo(mundo_nuevo);
}
