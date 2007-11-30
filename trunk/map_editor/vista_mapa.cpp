//HEADER
#include "vista_mapa.h"

/* CLASE VISTA_MAPA: Clase que representa la interfaz grafica del mapa en el editor. */

//Constructor:

VistaMapa::VistaMapa(S_ptr<Nivel> nivel){
	
	this->nivel = nivel;
	
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
	
	g_signal_connect(G_OBJECT(this->swindow), "button_press_event", G_CALLBACK(click_handler), this);
	
	//Creo la matriz de imagenes. Primero creo las filas.
	this->imagenes = new GtkWidget** [this->nivel->get_mapa()->get_alto()];
	//Por cada fila creo las columnas
	for (int i = 0; i < this->nivel->get_mapa()->get_alto(); i++)
		this->imagenes[i] = new GtkWidget* [this->nivel->get_mapa()->get_ancho()];
	//Inicializo las imagenes
	for (int i = 0; i < this->nivel->get_mapa()->get_alto(); i++)
		for (int j = 0; j < this->nivel->get_mapa()->get_ancho(); j++)
			imagenes[i][j] = NULL;

	this->dibujar();
}

//Destructor:

VistaMapa::~VistaMapa(){
	//Elimino la matriz de imagenes
	//Por cada fila elimino las columnas
	for (int i = 0; i < this->nivel->get_mapa()->get_alto(); i++)
		delete[](this->imagenes[i]);
	//Elimino las filas
	delete[](this->imagenes);
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
			if (!elem.es_nulo()){
				if ((elem->get_pos_x() == cont1) && (elem->get_pos_y() == cont2)){
					this->dibujar_elemento(elem);
				}
			} else {
				this->dibujar_casillero_vacio(cont1, cont2);
			}
			cont2++;
		}
		cont2 = 0;
		cont1++;
	 }
}

/* Dibujar Elemento: */

void VistaMapa::dibujar_elemento(S_ptr<Elemento> elem){
		GtkWidget* imagen;
		int pos_x = elem->get_pos_x();
		int pos_y = elem->get_pos_y();
		imagen = gtk_image_new();
		gtk_image_set_from_file(GTK_IMAGE(imagen), elem->get_ruta_imagen());
		gtk_table_attach_defaults (GTK_TABLE (this->tabla), imagen, pos_y, pos_y + elem->get_ancho(), pos_x, pos_x + elem->get_alto());
		for (int i = pos_x; i < pos_x + elem->get_alto(); i++)
			for (int j = pos_y; j < pos_y + elem->get_ancho(); j++)
					this->imagenes[i][j] = imagen;
		gtk_widget_show(imagen);
}

/* Dibujar Casillero Vacio: */

void VistaMapa::dibujar_casillero_vacio(int pos_x, int pos_y){
		GtkWidget* imagen;
		imagen = gtk_image_new();
		gtk_image_set_from_file(GTK_IMAGE(imagen), RUTA_VACIO);
		gtk_table_attach_defaults (GTK_TABLE (this->tabla), imagen, pos_y, pos_y + 1, pos_x, pos_x + 1);
		this->imagenes[pos_x][pos_y] = imagen;
		gtk_widget_show(imagen);
}

/* Borrar Elemento: */

void VistaMapa::borrar_elemento(S_ptr<Elemento> elem){
		if (!elem.es_nulo()){
			int pos_x = elem->get_pos_x();
			int pos_y = elem->get_pos_y();
			int alto = elem->get_alto();
			int ancho = elem->get_ancho();
			gtk_container_remove(GTK_CONTAINER(this->tabla), imagenes[pos_x][pos_y]);
			for (int i = pos_x; i < pos_x + alto; i++)
				for (int j = pos_y; j < pos_y + ancho; j++)
					this->imagenes[i][j] = NULL;
		}
}

/* Borrar Casillero Vacio: */

void VistaMapa::borrar_casillero_vacio(int pos_x, int pos_y){
		if (imagenes[pos_x][pos_y] != NULL){
			gtk_container_remove(GTK_CONTAINER(this->tabla), imagenes[pos_x][pos_y]);
			this->imagenes[pos_x][pos_y] = NULL;
		}
}

/* Agregar Elemento: */

void VistaMapa::agregar_elemento(double posX, double posY){
	
	GtkAdjustment* adjh = gtk_scrolled_window_get_hadjustment(GTK_SCROLLED_WINDOW(this->swindow));
	GtkAdjustment* adjv = gtk_scrolled_window_get_vadjustment(GTK_SCROLLED_WINDOW(this->swindow));
	
	int pos_y = (int) ((posY + gtk_adjustment_get_value(adjh)) / 25);
	int pos_x = (int) ((posX + gtk_adjustment_get_value(adjv)) / 25);
	
	TipoElem tipo = ControlSeleccion::get_instance()->get_tipo_selec();
	Orientacion orientacion = ControlSeleccion::get_instance()->get_orientacion_selec();
	
	if (this->nivel->agregar_elemento(tipo, pos_x, pos_y, orientacion)){
		S_ptr<Elemento> elem = this->nivel->get_mapa()->get_casillero(pos_x, pos_y)->get_estructural();
		for (int i = elem->get_pos_x(); i < elem->get_pos_x() + elem->get_alto(); i++)
			for (int j = elem->get_pos_y(); j < elem->get_pos_y() + elem->get_ancho(); j++)
				this->borrar_casillero_vacio(i, j);
		this->dibujar_elemento(elem);
	}
}

/* Quitar Elemento: */

void VistaMapa::quitar_elemento(double posX, double posY){
	
	GtkAdjustment* adjh = gtk_scrolled_window_get_hadjustment(GTK_SCROLLED_WINDOW(this->swindow));
	GtkAdjustment* adjv = gtk_scrolled_window_get_vadjustment(GTK_SCROLLED_WINDOW(this->swindow));
	
	int pos_y = (int) ((posY + gtk_adjustment_get_value(adjh)) / 25);
	int pos_x = (int) ((posX + gtk_adjustment_get_value(adjv)) / 25);
	
	S_ptr<Casillero> casillero = this->nivel->get_mapa()->get_casillero(pos_x, pos_y);
	if (!casillero.es_nulo()){
		
		S_ptr<Elemento> elem = casillero->get_estructural();
		
		if ((!elem.es_nulo()) && (this->nivel->quitar_elemento(pos_x, pos_y))){
			
			this->borrar_elemento(elem);
			
			for (int i = elem->get_pos_x(); i < elem->get_pos_x() + elem->get_alto(); i++)
				for (int j = elem->get_pos_y(); j < elem->get_pos_y() + elem->get_ancho(); j++)
					this->dibujar_casillero_vacio(i,j);
		}
	}
}

/* Click Handler: */

gboolean VistaMapa::click_handler (GtkWidget      *widget, 
					 GdkEventButton *event,
					 gpointer        data)
{
	
	VistaMapa* vista_mapa = (VistaMapa*) data;
	
	if (event->button == 1)
		vista_mapa->agregar_elemento(event->y, event->x);
	else
		vista_mapa->quitar_elemento(event->y, event->x);
	
	return TRUE;
}
