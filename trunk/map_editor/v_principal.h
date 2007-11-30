//HEADER

#ifndef V_PRINCIPAL_H_
#define V_PRINCIPAL_H_

#include <gtk/gtk.h>
#include "definiciones.h"
#include "m_bar_factory.h"
#include "menu.h"
#include "vista_mapa.h"
#include "modelo.h"
#include "panel_mundo.h"
#include "panel_elems.h"
#include "control_seleccion.h"
#include "../common/smart_pointer.h"

/* CLASE VPRINCIPAL: Representa la ventana principal del editor de mapas. */

class VPrincipal {
   
   private:

	GtkWidget* window; //Referencia a la ventana principal en gtk
    GtkWidget* vbox_princ; //Caja que separa al menu del resto de la ventana
   	GtkWidget* hbox_princ; //Caja que separa al mapa de los paneles de herramientas
    GtkWidget* vbox_tools; //Caja que separa los distintos paneles de herramientas
    VistaMapa* vista_mapa; //Contiene la representacion grafica de un mapa
    PanelMundo* panel_mundo; //Contiene la lista de mapas del mundo y los botones para operar con los mismos
    PanelElems* panel_estruc; //Panel que contiene a los elementos estructurales
    PanelElems* panel_modif; //Panel que contiene a los elementos modificadores
    S_ptr<Menu> menubar; //Referencia a la barra de menus
   
   public:

	//Constructor: Genera la ventana principal con todos sus widgets.
	VPrincipal();
   
   	//Destructor: Libera los recursos consumidos por la ventana.
    ~VPrincipal();

	//Get Widget: Obtiene la representacion de la ventana como widget.
	GtkWidget* get_widget() const;

	//Mostrar: Muestra la ventana y todos los widgets que posee
	void mostrar();

   private:
	   
    //Construir: Se encarga de armar la ventana con todos los paneles internos
    void construir();
	
	//METODOS MANEJADORES DE EVENTOS

	/* Delete Event Handler: Función 'callback' para atender la señal del evento "delete_event" */

	static gboolean delete_event_handler(GtkWidget* widget, GdkEvent* event, gpointer data);
	
};

#endif
