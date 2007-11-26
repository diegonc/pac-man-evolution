//HEADER

#include "item_archivo.h"

/* CLASE ITEM ARCHIVO: Clase que representa el item "archivo" para el menu.
   Hereda de item, implementa el ejecutar para realizar la accion correspondiente cuando se lo clikea. */

//Constructor:

ItemArchivo::ItemArchivo() : Item(N_ARCHIVO){}

//Ejecutar:

void ItemArchivo::ejecutar(GtkWidget* widget, gpointer data){
	g_print("[Apretaste menu archivo]\n");
}
