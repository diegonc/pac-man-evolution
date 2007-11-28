//HEADER

#ifndef PANEL_MUNDO_H
#define PANEL_MUNDO_H

#include <gtk/gtk.h>
#include "definiciones.h"
#include "../common/smart_pointer.h"

/* CLASE PANEL_MUNDO: Clase que contiene una lista con todos los mapas pertenecientes
   al mundo, y botones para la administracion del mismo. */

class PanelMundo {
   
   private:

	GtkWidget* frame; //Marco con titulo
    GtkWidget* vbox; //Contenedor principal que divide la lista de los botones
    GtkWidget* panel_botones; //Contenedor de los botones
    GtkWidget* swindow; //Scrolled window para poder hacer scroll de la lista
    GtkWidget* lista_view; //Widget utilizado para mostrar la lista de mapas
    GtkListStore* lista_mapas; //List Store con la lista de mapas del modelo
   
   public:

	//Constructor: Genera el panel del mundo con todos sus componentes.
	PanelMundo();

	//Get Widget: Obtiene la representacion del panel como widget.
	GtkWidget* get_widget() const;

   private:
	
	/* Crear lista mapas: Se encarga de crear la estructura de datos y la vista
   	   de la lista de mapas */
    void crear_lista_mapas();
   
   	/* Crear panel botones: Se encarga de crear y configurar el panel de botones
       y cada boton en particular. */
    void crear_panel_botones();
   
};

#endif
