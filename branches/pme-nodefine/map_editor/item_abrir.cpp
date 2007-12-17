//HEADER

#include "item_abrir.h"

/* CLASE ITEM ABRIR: Clase que representa el item "abrir" para un menu.
   Hereda de item, implementa el ejecutar para realizar la accion correspondiente cuando se lo clikea. */

//Constructor:

ItemAbrir::ItemAbrir() : Item(N_ABRIR){}

//Ejecutar:

void ItemAbrir::ejecutar(GtkWidget* widget, gpointer data){
	S_ptr<FileChooser> file_chooser (new FileChooser("Abrir Mundo", 
													 GUI::get_instance(0,0)->get_ventana_principal()->get_widget(),
													 GTK_FILE_CHOOSER_ACTION_OPEN));
	file_chooser->ejecutar();
}
