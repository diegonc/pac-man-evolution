//HEADER

#ifndef PANEL_ELEMS_H
#define PANEL_ELEMS_H

#include <gtk/gtk.h>
#include "definiciones.h"
#include "item_elem.h"
#include "../common/smart_pointer.h"
#include "../common/observable.h"
#include <vector>

using namespace std;

/* CLASE PANEL_ELEMS: Clase que representa un panel que contiene elementos
   simbolizados por iconos seleccionables. */

class PanelElems : public Observable {
   
   private:

	GtkWidget* frame; //Marco con titulo
   	GtkWidget* swindow; //Scrolled window para poder hacer scroll de la lista de elems
    GtkWidget* icons_view; //Widget utilizado para mostrar a los iconos de los elementos
    GtkListStore* lista_elems; //List Store con la lista de los elementos a mostrar
   	vector<S_ptr<ItemElem> > items; //Vector de items contenidos en el panel
   
   public:

	//Constructor: Genera el panel completo, sin elementos. Se le coloca el titulo pasado por param.
	PanelElems(char* titulo);
   
   	//Destructor: Libera los recursos consumidos por el panel.
   	~PanelElems();

	//Get Widget: Obtiene la representacion del panel como widget.
	GtkWidget* get_widget() const;
   
    //Agregar Elemento: Agrega un elemento con tipo y orientacion e imagen segun los datos pasados por parametro
    void agregar_elemento(TipoElem tipo, Orientacion orientacion, char* ruta_imagen);
   
   private:
	
	/* Crear lista elems: Se encarga de crear la estructura de datos y la vista
   	   de la lista de elementos */
    void crear_lista_elems();
   
    /* Item Seleccionado: Determina la accion a realizar cuando se selecciona un item particular del panel */
    static void item_seleccionado(GtkIconView *iconview, gpointer user_data);
   
};

#endif
