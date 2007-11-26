//HEADER

#ifndef V_PRINCIPAL_H_
#define V_PRINCIPAL_H_

#include <gtk/gtk.h>
#include "definiciones.h"
#include "m_bar_factory.h"
#include "menu.h"
#include "../common/smart_pointer.h"

/* CLASE VPRINCIPAL: Representa la ventana principal del editor de mapas. */

class VPrincipal {
   
   private:

	GtkWidget* window; //Referencia a la ventana principal en gtk
	S_ptr<Menu> menubar; //Referencia a la barra de menus
   
   public:

	//Constructor: Genera la ventana principal con todos sus widgets.
	VPrincipal();

	//Get Widget: Obtiene la representacion de la ventana como widget.
	GtkWidget* get_widget() const;

	//Mostrar: Muestra la ventana y todos los widgets que posee
	void mostrar();

   private:
	
	//METODOS MANEJADORES DE EVENTOS

	/* Delete Event Handler: Función 'callback' para atender la señal del evento "delete_event" */

	static gboolean delete_event_handler(GtkWidget* widget, GdkEvent* event, gpointer data);
	
};

#endif
