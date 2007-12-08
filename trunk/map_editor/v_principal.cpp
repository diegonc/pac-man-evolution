//HEADER

#include "v_principal.h"

/* CLASE VPRINCIPAL: Representa la ventana principal del editor de mapas. 
   Se encarga de observar al modelo y mirar cuando cambia el mundo para
   actualizar a sus componentes. */

//Constructor:

VPrincipal::VPrincipal(){
	
	//Creo la ventana principal y la configuro
	this->window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_container_border_width (GTK_CONTAINER (this->window), BORDE);
	gtk_window_maximize(GTK_WINDOW(this->window)); //La ventana arranca maximizada
	gtk_window_set_title (GTK_WINDOW(this->window), TITULO);
	
	//Conecto las señales de delete event y destroy con los handlers para la ventana
	g_signal_connect(G_OBJECT(this->window), "delete_event", G_CALLBACK(delete_event_handler), NULL);
	g_signal_connect(G_OBJECT(this->window), "destroy", G_CALLBACK(destroy_handler), this);
	
	//Creo el control de seleccion y todos los paneles de herramientas
	ControlSeleccion::get_instance();
	this->panel_mundo = new PanelMundo();
	this->panel_estruc = new PanelElems("ESTRUCTURALES");
	this->panel_modif = new PanelElems("MODIFICADORES");
	
	//Agrego a esta ventana como observadora del modelo
	Modelo::get_instance()->agregar_observador(this);
	
	//Creo la vista del mapa
	this->vista_mapa = new VistaMapa();
	
	//Construyo la ventana
	this->construir();

}

//Destructor:

VPrincipal::~VPrincipal(){
	//Elimino todos los paneles de herramientas, la vista del mapa y el control de seleccion
	delete(this->panel_mundo);
	delete(this->panel_estruc);
	delete(this->panel_modif);
	delete(this->vista_mapa);
	ControlSeleccion::destroy();
}

//Get Widget:

GtkWidget* VPrincipal::get_widget() const {
	return this->window;
}

//Mostrar:
	
void VPrincipal::mostrar(){
	//Muestro la ventana y todos sus widgets
	gtk_widget_show_all (this->window);
}

//Actualizar:

void VPrincipal::actualizar(Observable * observable, void * param){
	Mundo* mundo = Modelo::get_instance()->get_mundo();
	mundo->agregar_observador(this->panel_mundo);
	mundo->set_cambio();
	mundo->avisar_observadores(NULL);
	panel_mundo->set_cambio();
	panel_mundo->avisar_observadores(NULL);
}

//Construir:

void VPrincipal::construir(){
	//Creo y configuro la vbox principal, que separa el menu del resto de la ventana
	this->vbox_princ = gtk_vbox_new (FALSE, 1);
	gtk_container_set_border_width (GTK_CONTAINER (this->vbox_princ), 1);
	gtk_container_add (GTK_CONTAINER (window), this->vbox_princ);

	//Creo una barra de menus y la agrego a la ventana principal
	S_ptr<MenuBarFactory> fab (new MenuBarFactory());
	this->menubar = fab->construir();
	gtk_box_pack_start (GTK_BOX (this->vbox_princ), menubar->get_widget(), FALSE, TRUE, 0);

	//Creo y configuro la hbox principal, que separa la vista del mapa de las barras de herramientas
	this->hbox_princ = gtk_hbox_new (FALSE, 1);
	gtk_container_set_border_width (GTK_CONTAINER (this->hbox_princ), 1);
	gtk_container_add (GTK_CONTAINER (this->vbox_princ), this->hbox_princ);
	
	//Creo y configuro la vbox que contiene las barras de herramientas
	this->vbox_tools = gtk_vbox_new(TRUE, 1);
	gtk_container_set_border_width (GTK_CONTAINER (this->vbox_tools), 1);
	gtk_box_pack_start (GTK_BOX (this->hbox_princ), this->vbox_tools, FALSE, TRUE, 0);
	
	//Agrego el panel de niveles a la ventana principal
	GtkWidget* p_mundo = this->panel_mundo->get_widget();
	gtk_box_pack_start (GTK_BOX (this->vbox_tools), p_mundo, FALSE, TRUE, 0);
	
	//Agrego el panel de estructurales a la ventana principal
	GtkWidget* p_estruc = this->panel_estruc->get_widget();
	gtk_box_pack_start (GTK_BOX (this->vbox_tools), p_estruc, FALSE, TRUE, 0);
	
	//Agrego el panel de modificadores a la ventana principal
	GtkWidget* p_modif = this->panel_modif->get_widget();
	gtk_box_pack_start (GTK_BOX (this->vbox_tools), p_modif, FALSE, TRUE, 0);
	
	//Lleno los paneles con los modificadores y los estructurales
	this->llenar_paneles();
	
	//Agrego al control de seleccion como observador de los paneles de elementos
	this->panel_estruc->agregar_observador(ControlSeleccion::get_instance());
	this->panel_modif->agregar_observador(ControlSeleccion::get_instance());
	
	//Agrego a la vista del mapa como observadora del panel de niveles
	this->panel_mundo->agregar_observador(this->vista_mapa);
	
	//Agrego al panel mundo como observador del mundo
	Modelo::get_instance()->get_mundo()->agregar_observador(this->panel_mundo);
	
	//Agrego el widget de la vista del mapa a la ventana principal
	gtk_container_add (GTK_CONTAINER (this->hbox_princ), this->vista_mapa->get_widget());
}

//Llenar Paneles:

void VPrincipal::llenar_paneles(){
	//Agrego los estructurales y los modificadores a los paneles
	this->panel_estruc->agregar_elemento(PASILLO, ESTE, RUTA_PAS_HORIZ);
	this->panel_estruc->agregar_elemento(PASILLO, NORTE, RUTA_PAS_VERT);
	this->panel_estruc->agregar_elemento(ESQ, ESTE, RUTA_ESQ_ESTE);
	this->panel_estruc->agregar_elemento(ESQ, SUR, RUTA_ESQ_SUR);
	this->panel_estruc->agregar_elemento(ESQ, OESTE, RUTA_ESQ_OESTE);
	this->panel_estruc->agregar_elemento(ESQ, NORTE, RUTA_ESQ_NORTE);
	this->panel_estruc->agregar_elemento(CASA, ESTE, RUTA_CASA_ESTE);
	this->panel_estruc->agregar_elemento(CASA, SUR, RUTA_CASA_SUR);
	this->panel_estruc->agregar_elemento(CASA, OESTE, RUTA_CASA_OESTE);
	this->panel_estruc->agregar_elemento(CASA, NORTE, RUTA_CASA_NORTE);
	this->panel_modif->agregar_elemento(PWUP, NULA, RUTA_POWER_UP);
	this->panel_modif->agregar_elemento(BONUS, NULA, RUTA_BONUS);
	this->panel_modif->agregar_elemento(SALIDA, NULA, RUTA_SALIDA);
}

// Delete Event Handler:

gboolean VPrincipal::delete_event_handler(GtkWidget* widget, GdkEvent* event, gpointer data) {
	
	/* finaliza el loop de gtk_main() y libera memoria */
	gtk_main_quit();
	
	/* Devuelve FALSE, asi que la ventana se destruye */
	return FALSE;
}

/* Destroy Handler: */

gboolean VPrincipal::destroy_handler(GtkWidget* widget, gpointer data){
	//Devuelvo true y destruyo la ventana
	return TRUE;
}
