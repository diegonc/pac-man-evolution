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
	
	GtkWidget* p_modif = this->panel_modif->get_widget();
	gtk_box_pack_start (GTK_BOX (this->vbox_tools), p_modif, FALSE, TRUE, 0);;
	
	GtkWidget* tabla = gtk_table_new(15,15,TRUE);
	
	GtkWidget* viewport = gtk_viewport_new (NULL, NULL);
	GtkWidget* swindow = gtk_scrolled_window_new(gtk_viewport_get_hadjustment(GTK_VIEWPORT(viewport)), gtk_viewport_get_vadjustment(GTK_VIEWPORT(viewport)));
	
	for (int cont1 = 0; cont1 < 15; cont1++)
		for (int cont2 = 0; cont2 < 15; cont2++){
			GtkWidget* casillero = gtk_frame_new(NULL);
			gtk_table_attach_defaults (GTK_TABLE (tabla), casillero, cont1, cont1 + 1, cont2, cont2 + 1);
		 }

	gtk_container_add(GTK_CONTAINER(swindow), tabla);
	gtk_container_add(GTK_CONTAINER(this->hbox_princ), swindow);
}

// Delete Event Handler:

gboolean VPrincipal::delete_event_handler(GtkWidget* widget, GdkEvent* event, gpointer data) {
	
	/* finaliza el loop de gtk_main() y libera memoria */
	gtk_main_quit();
	
	/* Devuelve FALSE, asi que la ventana se destruye */
	return FALSE;
}
