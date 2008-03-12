//HEADER

#ifndef SUBMENU_H_
#define SUBMENU_H_

#include "menu.h"

/* CLASE SUBMENU : Clase que se ocupa de encapsular un submenu. Hereda de menu.
   Contiene instancias de la clase item. */

class SubMenu : public Menu {

	private:
		GtkWidget* submenu; //Referencia al submenu como widget de gtk

	public:

	//Constructor: Inicializa el submenu. Crea el widget sin items.
	SubMenu();

	//Get Widget: Obtiene la representacion del menu como widget.
	virtual GtkWidget* get_widget() const;

};

#endif
