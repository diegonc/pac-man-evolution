//HEADER

#include "item_abrir.h"

/* CLASE ITEM ABRIR: Clase que representa el item "abrir" para un menu.
   Hereda de item, implementa el ejecutar para realizar la accion correspondiente cuando se lo clikea. */

//Constructor:

ItemAbrir::ItemAbrir() : Item(N_ABRIR){}

//Ejecutar:

void ItemAbrir::ejecutar(GtkWidget* widget, gpointer data){
	g_print("[Apretaste menu archivo->abrir]\n");
}
