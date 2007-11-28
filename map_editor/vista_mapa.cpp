//HEADER
#include "vista_mapa.h"

/* CLASE VISTA_MAPA: Clase que representa la interfaz grafica del mapa en el editor. */

//Constructor:

VistaMapa::VistaMapa(S_ptr<Nivel> nivel){
	this->frame = gtk_frame_new("  MAPA  ");
	GtkWidget* viewport = gtk_viewport_new (NULL, NULL);
	this->swindow = gtk_scrolled_window_new(gtk_viewport_get_hadjustment(GTK_VIEWPORT(viewport)), gtk_viewport_get_vadjustment(GTK_VIEWPORT(viewport)));
	
	GtkWidget* vbox = gtk_vbox_new(FALSE,0);
	GtkWidget* hbox = gtk_hbox_new(FALSE,0);
	gtk_box_pack_start (GTK_BOX (vbox), hbox, FALSE, FALSE, 0);
	
	gtk_container_add(GTK_CONTAINER(this->frame), this->swindow);
	
	this->tabla = gtk_table_new(nivel->get_mapa()->get_alto(),nivel->get_mapa()->get_ancho(),FALSE);
	gtk_box_pack_start (GTK_BOX (hbox), this->tabla, FALSE, FALSE, 0);
	gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(this->swindow), vbox);
	
	this->nivel = nivel;
	this->dibujar();
}

//Get Widget:

GtkWidget* VistaMapa::get_widget() const{
	return this->frame;
}

//Dibujar:

void VistaMapa::dibujar() {
	int cont1 = 0; int cont2 = 0;
	Mapa* mapa = this->nivel->get_mapa();
	while (cont1 < mapa->get_alto()){
		while (cont2 < mapa->get_ancho()){
			S_ptr<Elemento> elem = mapa->get_casillero(cont1, cont2)->get_estructural();
			GtkWidget* imagen;
			if (!elem.es_nulo()){
				if ((elem->get_pos_x() == cont1) && (elem->get_pos_y() == cont2)){
					imagen = gtk_image_new();
					gtk_image_set_from_file(GTK_IMAGE(imagen), elem->get_ruta_imagen());
					gtk_table_attach_defaults (GTK_TABLE (this->tabla), imagen, cont2, cont2 + elem->get_ancho(), cont1, cont1 + elem->get_alto());
				}
			} else {
					imagen = gtk_image_new();
					gtk_image_set_from_file(GTK_IMAGE(imagen), RUTA_VACIO);
					gtk_table_attach_defaults (GTK_TABLE (this->tabla), imagen, cont2, cont2 + 1, cont1, cont1 + 1);
				}
			cont2++;
		}
		cont2 = 0;
		cont1++;
	 }
}
