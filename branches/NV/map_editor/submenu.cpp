//HEADER

#include "submenu.h"

/* CLASE SUBMENU : Clase que se ocupa de encapsular un submenu. Hereda de menu.
   Contiene instancias de la clase item. */

//Constructor:

SubMenu::SubMenu() : Menu(){
	this->submenu = gtk_menu_new();
}

//Get Widget:

GtkWidget* SubMenu::get_widget() const{
	return this->submenu;
}
