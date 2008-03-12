//HEADER

#ifndef M_BAR_FACTORY_H_
#define M_BAR_FACTORY_H_

#include <gtk/gtk.h>
#include "definiciones.h"
#include "m_arch_factory.h"
#include "item_archivo.h"
#include "menubar.h"
#include "../common/smart_pointer.h"

/* CLASE MENU BAR FACTORY: Clase que se ocupa de encapsular la creación de la barra de menus. */

class MenuBarFactory {

	public:

	//Construir: Construye la barra de menus y la devuelve.

	S_ptr<Menu> construir();

};

#endif
