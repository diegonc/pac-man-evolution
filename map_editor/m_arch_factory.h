//HEADER

#ifndef M_ARCH_FACTORY_H_
#define M_ARCH_FACTORY_H_

#include <gtk/gtk.h>
#include <editor/definiciones.h>
#include "item_nuevo.h"
#include "item_abrir.h"
#include "item_guardar.h"
#include "item_salir.h"
#include "menu.h"
#include "submenu.h"
#include <common/smart_pointer.h>


/* CLASE MENU ARCH FACTORY: Clase que se ocupa de encapsular la creación del menu archivo para el editor de mapas. */

class MenuArchFactory {

	public:

	//Construir: Construye un menu archivo y lo devuelve.

	S_ptr<Menu> construir();

};

#endif
