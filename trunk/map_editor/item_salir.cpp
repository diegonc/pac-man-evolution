//HEADER

#include "item_salir.h"

/* CLASE ITEM SALIR: Clase que representa el item "salir" para un menu.
   Hereda de item, implementa el ejecutar para realizar la accion correspondiente cuando se lo clikea. */

//Constructor:

ItemSalir::ItemSalir() : Item(N_SALIR){}

//Ejecutar:

void ItemSalir::ejecutar(GtkWidget* widget, gpointer data){
	g_print("[Apretaste menu archivo->salir]\n");
	gtk_main_quit();
}
