//Header
#include "panel_elems.h"

/* CLASE PANEL_ELEMS: Clase que representa un panel que contiene elementos
   simbolizados por iconos seleccionables. */

//Constructor:

PanelElems::PanelElems(char* titulo){
	this->frame = gtk_frame_new(titulo);
	
	this->crear_lista_elems();
}

//Get Widget:

GtkWidget* PanelElems::get_widget() const{
	return this->frame;
}

/* Crear lista elems: */
   
void PanelElems::crear_lista_elems(){
	this->lista_elems = gtk_list_store_new (1, GDK_TYPE_PIXBUF);
	this->icons_view = gtk_icon_view_new_with_model(GTK_TREE_MODEL(this->lista_elems));
	GtkWidget* viewport = gtk_viewport_new (NULL, NULL);
	this->swindow = gtk_scrolled_window_new(gtk_viewport_get_hadjustment(GTK_VIEWPORT(viewport)), gtk_viewport_get_vadjustment(GTK_VIEWPORT(viewport)));
	gtk_container_add(GTK_CONTAINER(this->swindow), this->icons_view);
	gtk_container_add(GTK_CONTAINER(this->frame), this->swindow);
}
