//HEADER

#ifndef MENU_H_
#define MENU_H_

#include <gtk/gtk.h>
#include "definiciones.h"
#include "item.h"
#include "../common/smart_pointer.h"
#include <list>

class Item; //Forward Declaration

/* CLASE ABSTRACTA MENU : Clase que se ocupa de encapsular el manejo de un menu. 
   Contiene instancias de la clase item. */

class Menu {

	private:

		std::list<S_ptr<Item> > items; //Items contenidos en el menu

	public:

	//Constructor: Inicializa el menu. Crea el widget sin items.
	Menu();

	//Destructor: Destruye el menu, liberando la memoria consumida por el mismo
	virtual ~Menu();

	//Get Widget: Obtiene la representacion del menu como widget.
	virtual GtkWidget* get_widget() const = 0;

	//Agregar Item: Agrega un nuevo item al menu.
	void agregar_item(S_ptr<Item> item);

};

#endif
