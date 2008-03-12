//HEADER

#include "menubar.h"

/* CLASE MENUBAR : Clase que se ocupa de encapsular una barra de menus. Hereda de menu.
   Contiene instancias de la clase item. */

//Constructor:

MenuBar::MenuBar() : Menu(){
	this->menubar = gtk_menu_bar_new();
}

//Get Widget:

GtkWidget* MenuBar::get_widget() const{
	return this->menubar;
}
