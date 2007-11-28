//HEADER

#ifndef PANEL_ELEMS_H
#define PANEL_ELEMS_H

#include <gtk/gtk.h>
#include "definiciones.h"
#include "../common/smart_pointer.h"

/* CLASE PANEL_ELEMS: Clase que representa un panel que contiene elementos
   simbolizados por iconos seleccionables. */

class PanelElems {
   
   private:

	GtkWidget* frame; //Marco con titulo
   	GtkWidget* swindow; //Scrolled window para poder hacer scroll de la lista de elems
    GtkWidget* icons_view; //Widget utilizado para mostrar a los iconos de los elementos
    GtkListStore* lista_elems; //List Store con la lista de los elementos a mostrar
   
   public:

	//Constructor: Genera el panel completo, sin elementos. Se le coloca el titulo pasado por param.
	PanelElems(char* titulo);

	//Get Widget: Obtiene la representacion del panel como widget.
	GtkWidget* get_widget() const;

   private:
	
	/* Crear lista elems: Se encarga de crear la estructura de datos y la vista
   	   de la lista de elementos */
    void crear_lista_elems();
   
};

#endif
