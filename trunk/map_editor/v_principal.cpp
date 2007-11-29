//HEADER

#include "v_principal.h"

/* CLASE VPRINCIPAL: Representa la ventana principal del editor de mapas. */

//Constructor:

VPrincipal::VPrincipal(){
	
	//Creo la ventana principal y la configuro
	this->window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_container_border_width (GTK_CONTAINER (this->window), BORDE);
	gtk_window_maximize(GTK_WINDOW(this->window)); //La ventana arranca maximizada
	gtk_window_set_title (GTK_WINDOW(this->window), TITULO);
	
	//Conecto la señal delete event con el handler para la ventana
	g_signal_connect(G_OBJECT(this->window), "delete_event", G_CALLBACK(delete_event_handler), NULL);
	
	this->panel_mundo = new PanelMundo();
	this->panel_estruc = new PanelElems("ESTRUCTURALES");
	this->panel_modif = new PanelElems("MODIFICADORES");
	
	this->construir();

}

//Destructor:

VPrincipal::~VPrincipal(){
	delete(this->panel_mundo);
	delete(this->panel_estruc);
	delete(this->panel_modif);
	delete(this->vista_mapa);
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

//Construir:

void VPrincipal::construir(){
	this->vbox_princ = gtk_vbox_new (FALSE, 1);
	gtk_container_set_border_width (GTK_CONTAINER (this->vbox_princ), 1);
	gtk_container_add (GTK_CONTAINER (window), this->vbox_princ);

	//Creo una barra de menus y la agrego a la ventana principal
	S_ptr<MenuBarFactory> fab (new MenuBarFactory());
	this->menubar = fab->construir();
	gtk_box_pack_start (GTK_BOX (this->vbox_princ), menubar->get_widget(), FALSE, TRUE, 0);

	this->hbox_princ = gtk_hbox_new (FALSE, 1);
	gtk_container_set_border_width (GTK_CONTAINER (this->hbox_princ), 1);
	gtk_container_add (GTK_CONTAINER (this->vbox_princ), this->hbox_princ);
	
	this->vbox_tools = gtk_vbox_new(TRUE, 1);
	gtk_container_set_border_width (GTK_CONTAINER (this->vbox_tools), 1);
	gtk_box_pack_start (GTK_BOX (this->hbox_princ), this->vbox_tools, FALSE, TRUE, 0);
	
	GtkWidget* p_mundo = this->panel_mundo->get_widget();
	gtk_box_pack_start (GTK_BOX (this->vbox_tools), p_mundo, FALSE, TRUE, 0);
	
	GtkWidget* p_estruc = this->panel_estruc->get_widget();
	gtk_box_pack_start (GTK_BOX (this->vbox_tools), p_estruc, FALSE, TRUE, 0);
	
	this->panel_estruc->agregar_elemento(RUTA_PAS_HORIZ);
	this->panel_estruc->agregar_elemento(RUTA_ESQ_ESTE);
	this->panel_estruc->agregar_elemento(RUTA_PAS_VERT);
	
	GtkWidget* p_modif = this->panel_modif->get_widget();
	gtk_box_pack_start (GTK_BOX (this->vbox_tools), p_modif, FALSE, TRUE, 0);
	
	//Creo un modelo
 	Modelo* modelo = new Modelo();
  	//Obtengo su mundo
    Mundo* mundo = modelo->get_mundo();
    //Agrego un nivel de 10 x 10
    mundo->agregar_nivel(10, 10);
	mundo->agregar_elemento(PASILLO, 1, 0, 1, ESTE);
	mundo->agregar_elemento(PASILLO, 1, 0, 4, ESTE);
	mundo->agregar_elemento(ESQ, 1, 0, 7, SUR);
	mundo->agregar_elemento(PASILLO, 1, 2, 8, NORTE);
	mundo->agregar_elemento(ESQ, 1, 5, 5, ESTE);
	
  	this->vista_mapa = new VistaMapa(mundo->get_nivel(1));
	gtk_container_add (GTK_CONTAINER (this->hbox_princ), this->vista_mapa->get_widget());
	
	delete(modelo);
	
}

// Delete Event Handler:

gboolean VPrincipal::delete_event_handler(GtkWidget* widget, GdkEvent* event, gpointer data) {
	
	/* finaliza el loop de gtk_main() y libera memoria */
	gtk_main_quit();
	
	/* Devuelve FALSE, asi que la ventana se destruye */
	return FALSE;
}