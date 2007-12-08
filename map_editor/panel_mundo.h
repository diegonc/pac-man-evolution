//HEADER

#ifndef PANEL_MUNDO_H
#define PANEL_MUNDO_H

#include <gtk/gtk.h>
#include "definiciones.h"
#include "modelo.h"
#include "gui.h"
#include "v_ingreso_datos.h"
#include "../common/smart_pointer.h"
#include "../common/observable.h"
#include "../common/observador.h"
#include <vector>

/* CLASE PANEL_MUNDO: Clase que contiene una lista con todos los mapas pertenecientes
   al mundo, y botones para la administracion del mismo. */

class PanelMundo : public Observable, public Observador {
   
   private:

	GtkWidget* frame; //Marco con titulo
    GtkWidget* vbox; //Contenedor principal que divide la lista de los botones
    GtkWidget* panel_botones; //Contenedor de los botones
    GtkWidget* swindow; //Scrolled window para poder hacer scroll de la lista
    GtkWidget* lista_view; //Widget utilizado para mostrar la lista de mapas
    GtkListStore* lista_mapas; //List Store con la lista de mapas del modelo
   	vector<S_ptr<Nivel> > niveles; //Vector de niveles contenidos en el panel
   	int seleccionado; //Nro de orden del item seleccionado actualmente. Si no hay nada seleccionado vale -1.
   
   public:

	//Constructor: Genera el panel del mundo con todos sus componentes.
	PanelMundo();
   
    //Destructor: Libera los recursos consumidos por el panel.
   	~PanelMundo();

	//Get Widget: Obtiene la representacion del panel como widget.
	GtkWidget* get_widget() const;
   
   	//Actualizar: Redibuja la lista con los niveles contenidos en el mundo actual.
	void actualizar(Observable * observable, void * param);

   private:
   
   	/* Redibujar: Redibuja la list view con los niveles contenidos en el vector 
       de niveles del panel. */
    void redibujar();
   
	/* Crear lista mapas: Se encarga de crear la estructura de datos y la vista
   	   de la lista de mapas */
    void crear_lista_mapas();
   
   	/* Crear panel botones: Se encarga de crear y configurar el panel de botones
       y cada boton en particular. */
    void crear_panel_botones();
   
    /* Item Seleccionado: Determina la accion a realizar cuando se selecciona un item particular de la lista de niveles. */
    static void item_seleccionado(GtkTreeView *treeview, gpointer user_data);
   
   	/* Agregar Click Handler: Determina la accion a realizar cuando se presiona el boton agregar nivel */
   	static void agregar_click_handler(GtkWidget *widget, gpointer user_data);
   
    /* Quitar Click Handler: Determina la accion a realizar cuando se presiona el boton quitar nivel */
   	static void quitar_click_handler(GtkWidget *widget, gpointer user_data);
	
	/* Subir Click Handler: Determina la accion a realizar cuando se presiona el boton subir nivel */
   	static void subir_click_handler(GtkWidget *widget, gpointer user_data);
	
	/* Bajar Click Handler: Determina la accion a realizar cuando se presiona el boton bajar nivel */
   	static void bajar_click_handler(GtkWidget *widget, gpointer user_data);
   
};

#endif
