//HEADER
#include "panel_mundo.h"

/* CLASE PANEL_MUNDO: Clase que contiene una lista con todos los mapas pertenecientes
   al mundo, y botones para la administracion del mismo. */

//Constructor:

PanelMundo::PanelMundo(){
	this->frame = gtk_frame_new("LISTA DE NIVELES");
	
	this->vbox = gtk_vbox_new (FALSE, 1);
	gtk_container_set_border_width (GTK_CONTAINER (this->vbox), 1);
	gtk_container_add (GTK_CONTAINER (this->frame), this->vbox);
	
	this->crear_lista_mapas();
	
	this->crear_panel_botones();
	
}

//Get Widget:

GtkWidget* PanelMundo::get_widget() const{
	return this->frame;
}

/* Crear lista mapas: */

void PanelMundo::crear_lista_mapas(){
	this->lista_mapas = gtk_list_store_new (2, G_TYPE_INT, G_TYPE_STRING);
	this->lista_view = gtk_tree_view_new_with_model(GTK_TREE_MODEL(this->lista_mapas));
  	GtkWidget* viewport = gtk_viewport_new (NULL, NULL);
	this->swindow = gtk_scrolled_window_new(gtk_viewport_get_hadjustment(GTK_VIEWPORT(viewport)), gtk_viewport_get_vadjustment(GTK_VIEWPORT(viewport)));
	gtk_container_add(GTK_CONTAINER(this->swindow), this->lista_view);
	gtk_container_add(GTK_CONTAINER(this->vbox), this->swindow);
	
	gtk_tree_view_set_headers_visible (GTK_TREE_VIEW(this->lista_view), TRUE);
	
	GtkCellRenderer     *renderer;

	renderer = gtk_cell_renderer_text_new ();
	gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (this->lista_view),
											   -1,      
											   "NRO NIVEL",  
											   renderer,
											   "text", 0,
											   NULL);

	renderer = gtk_cell_renderer_text_new ();
	gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (this->lista_view),
											   -1,      
											   "NOMBRE",  
											   renderer,
											   "text", 1,
											   NULL);
	
	GtkTreeIter    iter;
	
	for (int i=0; i<20; i++){
		gtk_list_store_append (this->lista_mapas, &iter);
		gtk_list_store_set (this->lista_mapas, &iter,
						  0, i,
						  1, "mapa.xml",
						  -1);
	}
}

/* Crear panel botones: */

void PanelMundo::crear_panel_botones(){
	
	this->panel_botones = gtk_hbox_new (FALSE, 10);
	gtk_container_set_border_width (GTK_CONTAINER (this->panel_botones), 1);
	gtk_box_pack_start (GTK_BOX (this->vbox), this->panel_botones, FALSE, TRUE, 0);
	
	GtkWidget* insertar = gtk_button_new_with_label(" AGREGAR ");
	GtkWidget* quitar = gtk_button_new_with_label(" QUITAR ");
	GtkWidget* subir = gtk_button_new_with_label(" SUBIR ");
	GtkWidget* bajar = gtk_button_new_with_label(" BAJAR ");
	
	gtk_box_pack_start (GTK_BOX (this->panel_botones), insertar, FALSE, TRUE, 0);
	gtk_box_pack_start (GTK_BOX (this->panel_botones), quitar, FALSE, TRUE, 0);
	gtk_box_pack_start (GTK_BOX (this->panel_botones), subir, FALSE, TRUE, 0);
	gtk_box_pack_start (GTK_BOX (this->panel_botones), bajar, FALSE, TRUE, 0);
	
}
