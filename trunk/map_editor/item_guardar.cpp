//HEADER

#include "item_guardar.h"

/* CLASE ITEM GUARDAR: Clase que representa el item "guardar" para un menu.
   Hereda de item, implementa el ejecutar para realizar la accion correspondiente cuando se lo clikea. */

//Constructor:

ItemGuardar::ItemGuardar() : Item(N_GUARDAR){}

//Ejecutar:

void ItemGuardar::ejecutar(GtkWidget* widget, gpointer data){
	g_print("[Apretaste menu archivo->guardar]\n");
}
