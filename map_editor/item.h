//HEADER

#ifndef ITEM_H_
#define ITEM_H_

#include <gtk/gtk.h>
#include "definiciones.h"
#include "menu.h"
#include "../common/smart_pointer.h"

class Menu; //Forward Declaration

/* CLASE ITEM: Clase abstacta que representa un item para un menu. */

class Item {

  private:

	GtkWidget* item; //Referencia al item en gtk
	S_ptr<Menu> submenu; //Referencia a un submenu si lo posee

  public:

	//Constructor: Construye un item para menu, con el label pasado como parametro
	Item(gchar* label);

	//Destructor Virtual:
	virtual ~Item(){}

	//Get Widget: Obtiene la representacion del menu item como widget.
	GtkWidget* get_widget() const;

	//Set Sub Menu: Agrega al item el submenu pasado como parametro, reemplazando el anterior si lo habia.
	//Si se manda NULL, se remueve el submenu actual.
	void set_sub_menu(S_ptr<Menu> submenu);

  private:

	//Ejecutar: Metodo virtual que ejecuta una accion determinada cuando se clikea el item en el menu.
	virtual void ejecutar(GtkWidget* widget, gpointer data) = 0;

	//Click Event Handler: Funcion estatica que se encarga de ejecutar la accion del item cuando se clickea al mismo.
	static void click_event_handler(GtkWidget* widget, gpointer data);

};

#endif
