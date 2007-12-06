//HEADER
#include "vista_mapa.h"

/* CLASE VISTA_MAPA: Clase que representa la interfaz grafica del mapa en el editor. */

//Constructor:

VistaMapa::VistaMapa(S_ptr<Nivel> nivel){
	
	this->nivel = nivel;
	
	this->frame = gtk_frame_new("  MAPA  ");
	GtkWidget* viewport = gtk_viewport_new (NULL, NULL);
	this->swindow = gtk_scrolled_window_new(gtk_viewport_get_hadjustment(GTK_VIEWPORT(viewport)), gtk_viewport_get_vadjustment(GTK_VIEWPORT(viewport)));
	
	this->vbox = gtk_vbox_new(FALSE,0);
	this->hbox = gtk_hbox_new(FALSE,0);
	gtk_box_pack_start (GTK_BOX (vbox), hbox, FALSE, FALSE, 0);
	
	this->tabla = gtk_table_new(nivel->get_mapa()->get_alto(),nivel->get_mapa()->get_ancho(),FALSE);
	gtk_box_pack_start (GTK_BOX (hbox), this->tabla, FALSE, FALSE, 0);
	
	gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(this->swindow), this->vbox);
	gtk_container_add(GTK_CONTAINER(this->frame), this->swindow);
	
	g_signal_connect(G_OBJECT(this->swindow), "button_press_event", G_CALLBACK(click_handler), this);
	
	this->inicializar_matriz(this->imagenes);
	this->inicializar_matriz(this->imag_modif);

	this->dibujar();
}

//Destructor:

VistaMapa::~VistaMapa(){
	this->liberar_matriz(this->imagenes);
	this->liberar_matriz(this->imag_modif);
}

//Get Widget:

GtkWidget* VistaMapa::get_widget() const{
	return this->frame;
}

//Actualizar:

void VistaMapa::actualizar(Observable * observable, void * param){
	S_ptr<Nivel> nivel = *((S_ptr<Nivel>*) param);
	this->redibujar(nivel);
}

//Inicializar Matriz:

void VistaMapa::inicializar_matriz(GtkWidget*** &matriz){
	//Creo la matriz de widgets. Primero creo las filas.
	matriz = new GtkWidget** [this->nivel->get_mapa()->get_alto()];
	//Por cada fila creo las columnas
	for (int i = 0; i < this->nivel->get_mapa()->get_alto(); i++)
		matriz[i] = new GtkWidget* [this->nivel->get_mapa()->get_ancho()];
	//Inicializo los widgets en null
	for (int i = 0; i < this->nivel->get_mapa()->get_alto(); i++)
		for (int j = 0; j < this->nivel->get_mapa()->get_ancho(); j++)
			matriz[i][j] = NULL;
}

//Liberar Matriz:

void VistaMapa::liberar_matriz(GtkWidget*** &matriz){
	//Elimino la matriz de widgets
	//Por cada fila elimino las columnas
	for (int i = 0; i < this->nivel->get_mapa()->get_alto(); i++)
		delete[](matriz[i]);
	//Elimino las filas
	delete[](matriz);
}

//Redibujar:

void VistaMapa::redibujar(S_ptr<Nivel> nivel){
	this->nivel = nivel;
	gtk_widget_destroy(this->tabla);
	this->tabla = gtk_table_new(nivel->get_mapa()->get_alto(),nivel->get_mapa()->get_ancho(),FALSE);
	gtk_box_pack_start (GTK_BOX (hbox), this->tabla, FALSE, FALSE, 0);
	gtk_widget_show(this->tabla);
	this->dibujar();
}

//Dibujar:

void VistaMapa::dibujar() {
	int cont1 = 0; int cont2 = 0;
	Mapa* mapa = this->nivel->get_mapa();
	while (cont1 < mapa->get_alto()){
		while (cont2 < mapa->get_ancho()){
			S_ptr<Casillero> casillero = mapa->get_casillero(cont1, cont2);
			S_ptr<Elemento> estruct = casillero->get_estructural();
			S_ptr<Elemento> modificador = casillero->get_modificador();
			if (!estruct.es_nulo()){
				if ((estruct->get_pos_x() == cont1) && (estruct->get_pos_y() == cont2))
					this->dibujar_elemento(estruct);
				if (!modificador.es_nulo())
					this->dibujar_elemento(modificador);
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
		GtkWidget* fixed;
		GtkWidget* imagenEstruc;
		GtkWidget* imagenModif;
		int pos_x = elem->get_pos_x();
		int pos_y = elem->get_pos_y();
		if (elem->es_estructural()){
			fixed = gtk_fixed_new();
			imagenEstruc = gtk_image_new();
			gtk_image_set_from_file(GTK_IMAGE(imagenEstruc), elem->get_ruta_imagen());
			gtk_fixed_put(GTK_FIXED(fixed), imagenEstruc, 0, 0);
			gtk_table_attach_defaults (GTK_TABLE (this->tabla), fixed, pos_y, pos_y + elem->get_ancho(), pos_x, pos_x + elem->get_alto());
			for (int i = pos_x; i < pos_x + elem->get_alto(); i++)
				for (int j = pos_y; j < pos_y + elem->get_ancho(); j++)
					this->imagenes[i][j] = fixed;
		} else {
			S_ptr<Elemento> estruct = this->nivel->get_mapa()->get_casillero(pos_x, pos_y)->get_estructural();
			fixed = this->imagenes[pos_x][pos_y];
			imagenModif = gtk_image_new();
			gtk_image_set_from_file(GTK_IMAGE(imagenModif), elem->get_ruta_imagen());
			gtk_fixed_put(GTK_FIXED(fixed), imagenModif, (pos_y - estruct->get_pos_y()) * 25, (pos_x - estruct->get_pos_x()) * 25);			
			this->imag_modif[pos_x][pos_y] = imagenModif;
		}
		gtk_widget_show_all(fixed);
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
			if (elem->es_estructural()) {
				int alto = elem->get_alto();
				int ancho = elem->get_ancho();
				gtk_container_remove(GTK_CONTAINER(this->tabla), imagenes[pos_x][pos_y]);
				for (int i = pos_x; i < pos_x + alto; i++)
					for (int j = pos_y; j < pos_y + ancho; j++){
						this->imagenes[i][j] = NULL;
						this->imag_modif[i][j] = NULL;
					}
			} else {
				GtkWidget* fixed = this->imagenes[pos_x][pos_y];
				gtk_container_remove(GTK_CONTAINER(fixed), imag_modif[pos_x][pos_y]);
				imag_modif[pos_x][pos_y] = NULL;
			}
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
		S_ptr<Casillero> casillero = this->nivel->get_mapa()->get_casillero(pos_x, pos_y);
		S_ptr<Elemento> elem = casillero->get_modificador();
		if (!casillero->tiene_modificador()){
			elem = casillero->get_estructural();
			for (int i = elem->get_pos_x(); i < elem->get_pos_x() + elem->get_alto(); i++)
				for (int j = elem->get_pos_y(); j < elem->get_pos_y() + elem->get_ancho(); j++)
					this->borrar_casillero_vacio(i, j);
		}
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
		
		if (casillero->tiene_modificador())
			elem = casillero->get_modificador();
		
		if ((!elem.es_nulo()) && (this->nivel->quitar_elemento(pos_x, pos_y))){
			
			this->borrar_elemento(elem);
			if (elem->es_estructural())
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
