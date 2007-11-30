//Header
#include "panel_elems.h"

/* CLASE PANEL_ELEMS: Clase que representa un panel que contiene elementos
   simbolizados por iconos seleccionables. */

//Constructor:

PanelElems::PanelElems(char* titulo){
	this->frame = gtk_frame_new(titulo);
	this->crear_lista_elems();
}

//Destructor:

PanelElems::~PanelElems(){
	this->items.clear();
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
	
	gtk_icon_view_set_pixbuf_column (GTK_ICON_VIEW(this->icons_view),0);
	
	gtk_icon_view_set_column_spacing (GTK_ICON_VIEW(this->icons_view),40);
	
	gtk_icon_view_set_row_spacing (GTK_ICON_VIEW(this->icons_view),20);
	
	gtk_icon_view_set_selection_mode(GTK_ICON_VIEW(this->icons_view), GTK_SELECTION_BROWSE);
	
	g_signal_connect(G_OBJECT(this->icons_view), "selection-changed", G_CALLBACK(item_seleccionado), this);
}

//Agregar Elemento:

void PanelElems::agregar_elemento(TipoElem tipo, Orientacion orientacion, char* ruta_imagen){
	
	GtkTreeIter  iter;
  	GdkPixbuf    *pixbuf;
  	GError       *error = NULL;

	pixbuf = gdk_pixbuf_new_from_file(ruta_imagen, &error);
	
	if (error)
	{
		g_critical ("Could not load pixbuf: %s\n", error->message);
		g_error_free(error);
		return;
	}
	
	gtk_list_store_append(this->lista_elems, &iter);
	gtk_list_store_set(this->lista_elems, &iter, 0, pixbuf,-1);
	g_object_unref(pixbuf);
	
	S_ptr<ItemElem> item (new ItemElem(tipo, orientacion, ruta_imagen));
	this->items.push_back(item);
	
}

//Item seleccionado:

void PanelElems::item_seleccionado(GtkIconView *iconview, gpointer user_data){
		GtkCellRenderer* cell = NULL;
		GtkTreePath* path = NULL;
		PanelElems* panel = (PanelElems*) user_data;
		gtk_icon_view_get_cursor (iconview, &path, &cell);
		if (path != NULL){
			int* int_path = gtk_tree_path_get_indices (path);
			S_ptr<ItemElem> item = panel->items[int_path[0]];
			gtk_tree_path_free(path);
			panel->set_cambio();
			panel->avisar_observadores(&item);
		}
}
