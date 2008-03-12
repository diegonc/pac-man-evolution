//HEADER

#include "menu.h"

/* CLASE MENU : Clase que se ocupa de encapsular un menu desplegable. 
   Contiene instancias de la clase item. */

//Constructor:

Menu::Menu(){}

//Destructor:

Menu::~Menu(){
	//Vacio la lista de items
	this->items.clear();
}

//Agregar Item:

void Menu::agregar_item(S_ptr<Item> item){
	gtk_menu_shell_append(GTK_MENU_SHELL(this->get_widget()), item->get_widget());
	this->items.push_back(item);
}
