//HEADER

#include "item_guardar.h"

/* CLASE ITEM GUARDAR: Clase que representa el item "guardar" para un menu.
   Hereda de item, implementa el ejecutar para realizar la accion correspondiente cuando se lo clikea. */

//Constructor:

ItemGuardar::ItemGuardar() : Item(N_GUARDAR){}

//Ejecutar:

void ItemGuardar::ejecutar(GtkWidget* widget, gpointer data){
	S_ptr<FileChooser> file_chooser (new FileChooser("Guardar Mundo", 
													 GUI::get_instance(0,0)->get_ventana_principal()->get_widget(),
													 GTK_FILE_CHOOSER_ACTION_SAVE));
	file_chooser->ejecutar();
}
