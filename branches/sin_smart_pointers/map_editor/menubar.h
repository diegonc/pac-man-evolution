//HEADER

#ifndef MENUBAR_H_
#define MENUBAR_H_

#include "menu.h"

/* CLASE MENUBAR : Clase que se ocupa de encapsular una barra de menus. Hereda de menu.
   Contiene instancias de la clase item. */

class MenuBar : public Menu {

	private:
		GtkWidget* menubar; //Referencia a la barra de menus como widget de gtk

	public:

	//Constructor: Inicializa la barra de menus. Crea el widget sin items.
	MenuBar();

	//Get Widget: Obtiene la representacion del menu como widget.
	virtual GtkWidget* get_widget() const;

};

#endif
