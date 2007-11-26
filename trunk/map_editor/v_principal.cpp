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
	
	GtkWidget* main_vbox = gtk_vbox_new (FALSE, 1);
	gtk_container_set_border_width (GTK_CONTAINER (main_vbox), 1);
	gtk_container_add (GTK_CONTAINER (window), main_vbox);

	//Creo una barra de menus y la agrego a la ventana principal
	S_ptr<MenuBarFactory> fab (new MenuBarFactory());
	this->menubar = fab->construir();
	gtk_box_pack_start (GTK_BOX (main_vbox), menubar->get_widget(), FALSE, TRUE, 0);

	GtkWidget* main_hbox = gtk_hbox_new (FALSE, 1);
	gtk_container_set_border_width (GTK_CONTAINER (main_vbox), 1);
	gtk_container_add (GTK_CONTAINER (main_vbox), main_hbox);

	GtkWidget* vbox1 = gtk_vbox_new (FALSE, 1);
	gtk_container_set_border_width (GTK_CONTAINER (vbox1), 1);
	gtk_container_add (GTK_CONTAINER (main_hbox), vbox1);

	GtkWidget* tabla = gtk_table_new(15,15,TRUE);
	
	for (int cont1 = 0; cont1 < 15; cont1++)
		for (int cont2 = 0; cont2 < 15; cont2++){
			GtkWidget* casillero = gtk_frame_new(NULL);
			gtk_table_attach_defaults (GTK_TABLE (tabla), casillero, cont1, cont1 + 1, cont2, cont2 + 1);
		 }

	gtk_container_add (GTK_CONTAINER (main_hbox), tabla);

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

// Delete Event Handler:

gboolean VPrincipal::delete_event_handler(GtkWidget* widget, GdkEvent* event, gpointer data) {
	
	/* finaliza el loop de gtk_main() y libera memoria */
	gtk_main_quit();
	
	/* Devuelve FALSE, asi que la ventana se destruye */
	return FALSE;
}
