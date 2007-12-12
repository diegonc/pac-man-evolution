//HEADER

#include "item.h"

/* CLASE ITEM: Clase abstacta que representa un item para un menu. */

//Constructor:

Item::Item(gchar* label){
	//Creo y muestro el menu item
	this->item = gtk_menu_item_new_with_label(label);
	//Conecto la señal activate con el handler
	g_signal_connect(G_OBJECT(this->item), "activate", G_CALLBACK(click_event_handler), this);
	gtk_widget_show  (this->item);
}

//Get Widget:

GtkWidget* Item::get_widget() const {
	return this->item;
}

//Set Sub Menu:

void Item::set_sub_menu(S_ptr<Menu> submenu){
	this->submenu = submenu;
	if (submenu.es_nulo())
		gtk_menu_item_set_submenu(GTK_MENU_ITEM(this->item), NULL);
	else
		gtk_menu_item_set_submenu(GTK_MENU_ITEM(this->item), submenu->get_widget());
}

//Click Event Handler:

void Item::click_event_handler(GtkWidget* widget, gpointer data){
	Item* instancia = (Item*) data;
	instancia->ejecutar(widget, data);
}
