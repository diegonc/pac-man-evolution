//HEADER
#include "panel_mundo.h"

/* CLASE PANEL_MUNDO: Clase que contiene una lista con todos los mapas pertenecientes
   al mundo, y botones para la administracion del mismo. */

//Constructor:

PanelMundo::PanelMundo(){
	//Creo un nuevo frame para contener todo lo demas
	this->frame = gtk_frame_new("LISTA DE NIVELES");
	//Creo una vbox para dividir a la lista de los botones y la agrego al frame
	this->vbox = gtk_vbox_new (FALSE, 1);
	gtk_container_set_border_width (GTK_CONTAINER (this->vbox), 1);
	gtk_container_add (GTK_CONTAINER (this->frame), this->vbox);
	//Creo la lista de mapas
	this->crear_lista_mapas();
	//Creo el panel de botones
	this->crear_panel_botones();
	//Aviso que al principio no hay ningun nivel seleccionado
	this->set_cambio();
	this->avisar_observadores(NULL);
	this->seleccionado = -1;
}
    
//Destructor: Libera los recursos consumidos por el panel.

PanelMundo::~PanelMundo(){
	this->niveles.clear();
}

//Get Widget:

GtkWidget* PanelMundo::get_widget() const{
	return this->frame;
}

//Actualizar:

void PanelMundo::actualizar(Observable * observable, void * param){
	//Cuando se actualiza el mundo, vuelvo a cargar los niveles
	Mundo* mundo = (Mundo*) observable;
	this->niveles.clear();
	for (unsigned int cont = 1; cont <= mundo->get_cant_niveles(); cont++)
		this->niveles.push_back(mundo->get_nivel(cont));
	//Redibujo la lista con los nuevos niveles
	this->redibujar();
	//Si la lista esta vacia aviso a los obs que no hay nada seleccionado
	if (niveles.empty()){
		this->set_cambio();
		this->avisar_observadores(NULL);
		this->seleccionado = -1;
	}
}

//Redibujar:

void PanelMundo::redibujar(){
	GtkTreeIter    iter;
	int posicion = 1;
	//Limpio la lista visible
	gtk_list_store_clear(this->lista_mapas);
	vector<S_ptr<Nivel> >::iterator it;
	//Cargo nuevamente los niveles en la lista a mostrar al usuario
	for (it = this->niveles.begin(); it != niveles.end(); ++it){
		S_ptr<Nivel> nivel = (*it);
		gtk_list_store_append (this->lista_mapas, &iter);
		gtk_list_store_set (this->lista_mapas, &iter, 0, posicion, 1, (nivel->get_nombre()).c_str(), -1);
		posicion++;
	}
}

//Item seleccionado:

void PanelMundo::item_seleccionado(GtkTreeView *treeview, gpointer user_data){
		GtkTreeViewColumn* columna = NULL;
		GtkTreePath* path = NULL;
		PanelMundo* panel = (PanelMundo*) user_data;
		//Cuando un item es seleccionado en la lista, obtengo el path del cursor
		gtk_tree_view_get_cursor (treeview, &path, &columna);
		if (path != NULL){
			//Lo paso como entero y obtengo el nivel desde ese path
			int* int_path = gtk_tree_path_get_indices (path);
			S_ptr<Nivel> nivel = panel->niveles[int_path[0]];
			panel->seleccionado = int_path[0];
			gtk_tree_path_free(path);
			//Mando a los obs que el nuevo nivel es el seleccionado
			panel->set_cambio();
			panel->avisar_observadores(&nivel);
		}
}

/* Crear lista mapas: */

void PanelMundo::crear_lista_mapas(){
	//Creo la lista de mapas visible y la vista de la lista
	this->lista_mapas = gtk_list_store_new (2, G_TYPE_INT, G_TYPE_STRING);
	this->lista_view = gtk_tree_view_new_with_model(GTK_TREE_MODEL(this->lista_mapas));
  	//Creo una ventana scrolleable para la lista
	GtkWidget* viewport = gtk_viewport_new (NULL, NULL);
	this->swindow = gtk_scrolled_window_new(gtk_viewport_get_hadjustment(GTK_VIEWPORT(viewport)), gtk_viewport_get_vadjustment(GTK_VIEWPORT(viewport)));
	gtk_container_add(GTK_CONTAINER(this->swindow), this->lista_view);
	gtk_container_add(GTK_CONTAINER(this->vbox), this->swindow);
	//Hago que sean visible las cabeceras de la lista
	gtk_tree_view_set_headers_visible (GTK_TREE_VIEW(this->lista_view), TRUE);
	//Inserto 2 columnas: Nro Nivel y Nombre del nivel
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
	//Conecto la señal de cambio de seleccion a la vista de la lista								   
	g_signal_connect(G_OBJECT(this->lista_view), "cursor-changed", G_CALLBACK(item_seleccionado), this);
}

/* Crear panel botones: */

void PanelMundo::crear_panel_botones(){
	//Creo una nueva hbox donde se pondran los botones
	this->panel_botones = gtk_hbox_new (FALSE, 10);
	gtk_container_set_border_width (GTK_CONTAINER (this->panel_botones), 1);
	gtk_box_pack_start (GTK_BOX (this->vbox), this->panel_botones, FALSE, TRUE, 0);
	
	//Creo cada boton
	GtkWidget* insertar = gtk_button_new_with_label(" AGREGAR ");
	GtkWidget* quitar = gtk_button_new_with_label(" QUITAR ");
	GtkWidget* subir = gtk_button_new_with_label(" SUBIR ");
	GtkWidget* bajar = gtk_button_new_with_label(" BAJAR ");
	
	//Coloco cada boton en la hbox
	gtk_box_pack_start (GTK_BOX (this->panel_botones), insertar, FALSE, TRUE, 0);
	gtk_box_pack_start (GTK_BOX (this->panel_botones), quitar, FALSE, TRUE, 0);
	gtk_box_pack_start (GTK_BOX (this->panel_botones), subir, FALSE, TRUE, 0);
	gtk_box_pack_start (GTK_BOX (this->panel_botones), bajar, FALSE, TRUE, 0);
	
	//Conecto las señales de click con el handler adecuado para cada boton
	g_signal_connect(G_OBJECT(insertar), "clicked", G_CALLBACK(agregar_click_handler), this);
	g_signal_connect(G_OBJECT(quitar), "clicked", G_CALLBACK(quitar_click_handler), this);
	g_signal_connect(G_OBJECT(subir), "clicked", G_CALLBACK(subir_click_handler), this);
	g_signal_connect(G_OBJECT(bajar), "clicked", G_CALLBACK(bajar_click_handler), this);
}

/* Agregar Click Handler: */

void PanelMundo::agregar_click_handler(GtkWidget *widget, gpointer user_data){
	PanelMundo* panel = (PanelMundo*) user_data;
	Mundo* mundo = Modelo::get_instance()->get_mundo();
	//Creo una nueva ventana de ingreso de datos y la ejecuto
	S_ptr<VIngDatos> ing_datos (new VIngDatos("Nuevo Nivel: ", 
												  GUI::get_instance(0,0)->get_ventana_principal()->get_widget()));
	if (ing_datos->ejecutar()){
		string nombre = ing_datos->get_nombre();
		int ancho = ing_datos->get_ancho();
		int alto = ing_datos->get_alto();
		mundo->agregar_nivel(nombre, alto, ancho);
		panel->seleccionado = mundo->get_cant_niveles() - 1;
		S_ptr<Nivel> nivel = Modelo::get_instance()->get_mundo()->get_nivel(panel->seleccionado + 1);
		panel->set_cambio();
		panel->avisar_observadores(&nivel);
	}
}

/* Quitar Click Handler: */

void PanelMundo::quitar_click_handler(GtkWidget *widget, gpointer user_data){
	PanelMundo* panel = (PanelMundo*) user_data;
	if (panel->seleccionado != -1)
		Modelo::get_instance()->get_mundo()->quitar_nivel(panel->seleccionado + 1);
	//Aviso que no queda ningun nivel seleccionado
	panel->set_cambio();
	panel->avisar_observadores(NULL);
	panel->seleccionado = -1;
}

/* Subir Click Handler: */

void PanelMundo::subir_click_handler(GtkWidget *widget, gpointer user_data){
	PanelMundo* panel = (PanelMundo*) user_data;
	if (panel->seleccionado != -1){
		Modelo::get_instance()->get_mundo()->promover(panel->seleccionado + 1);
		panel->seleccionado--;
		S_ptr<Nivel> nivel = Modelo::get_instance()->get_mundo()->get_nivel(panel->seleccionado + 1);
		panel->set_cambio();
		panel->avisar_observadores(&nivel);
	}
}

/* Bajar Click Handler: */

void PanelMundo::bajar_click_handler(GtkWidget *widget, gpointer user_data){
	PanelMundo* panel = (PanelMundo*) user_data;
	if (panel->seleccionado != -1) {
		Modelo::get_instance()->get_mundo()->degradar(panel->seleccionado + 1);
		panel->seleccionado++;
		S_ptr<Nivel> nivel = Modelo::get_instance()->get_mundo()->get_nivel(panel->seleccionado + 1);
		panel->set_cambio();
		panel->avisar_observadores(&nivel);
	}
}
