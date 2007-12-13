//HEADER
#include "vista_mapa.h"

/* CLASE VISTA_MAPA: Clase que representa la interfaz grafica del mapa en el editor. */

//Constructor:

VistaMapa::VistaMapa(){
	//Creo un frame y una scrolled window
	this->frame = gtk_frame_new("  MAPA  ");
	GtkWidget* viewport = gtk_viewport_new (NULL, NULL);
	this->swindow = gtk_scrolled_window_new(gtk_viewport_get_hadjustment(GTK_VIEWPORT(viewport)), gtk_viewport_get_vadjustment(GTK_VIEWPORT(viewport)));
	
	//Creo una vbox y una hbox para que el tamaño del mapa se pueda amoldar en ambas direcciones
	this->vbox = gtk_vbox_new(FALSE,0);
	this->hbox = gtk_hbox_new(FALSE,0);
	//Pongo la hbox dentro de la vbos
	gtk_box_pack_start (GTK_BOX (vbox), hbox, FALSE, FALSE, 0);
	
	//Agrego la vbox a la scrolled window y esta ultima al frame
	gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(this->swindow), this->vbox);
	gtk_container_add(GTK_CONTAINER(this->frame), this->swindow);
	
	//Conecto la señal de click sobre el mapa a la scrolled window
	g_signal_connect(G_OBJECT(this->swindow), "button_press_event", G_CALLBACK(click_handler), this);
	
	GError       *error = NULL;

	//Cargo los pixbuf
	this->pixbuf_vacio = gdk_pixbuf_new_from_file(RUTA_VACIO, &error);
	this->pixbuf_marca = gdk_pixbuf_new_from_file(RUTA_MARCA, &error);
	
	//Creo un actualizador de marcas y lo hago correr
	this->actualizador = new ActualizadorMarcas(this);
	//this->actualizador->start();
}

//Destructor:

VistaMapa::~VistaMapa(){
	//Si el nivel actual no es nulo libero las matrices
	if (!this->nivel.es_nulo()){
		this->liberar_matriz(this->imagenes);
		this->liberar_matriz(this->imag_modif);
		this->liberar_matriz(this->marcas);
	}
	//Freo la ejecucion del actualizador y le hago join
	//this->actualizador->frenar_ejecucion();
	//this->actualizador->join();
	//Borro el actualizador de marcas
	delete (this->actualizador);
}

//Get Widget:

GtkWidget* VistaMapa::get_widget() const{
	return this->frame;
}

//Actualizar:

void VistaMapa::actualizar(Observable * observable, void * param){
	//Obtengo el nuevo nivel a graficar desde el parametro.
	S_ptr<Nivel> nivel;
	if (param != NULL)
		nivel = *((S_ptr<Nivel>*) param);
	//Redibujo el nivel
	this->redibujar(nivel);
	//Aviso que hay un nuevo nivel
	this->set_cambio();
	this->avisar_observadores(&this->nivel);
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
	//Si habia un nivel antes, destruyo la parte grafica de ese nivel
	if (!this->nivel.es_nulo()){
		gtk_widget_destroy(this->tabla);
		this->tabla = NULL;
		this->liberar_matriz(this->imagenes);
		this->liberar_matriz(this->imag_modif);
		this->liberar_matriz(this->marcas);
	}
	//Asigno el nuevo nivel
	this->nivel = nivel;
	//Si el nivel no es nulo lo redibujo
	if (!nivel.es_nulo()){
		//Inicializo las matrices
		this->inicializar_matriz(this->imagenes);
		this->inicializar_matriz(this->imag_modif);
		this->inicializar_matriz(this->marcas);
		//Creo una nueva tabla y la meto en la hbox
		this->tabla = gtk_table_new(nivel->get_mapa()->get_alto(),nivel->get_mapa()->get_ancho(),FALSE);
		gtk_box_pack_start (GTK_BOX (hbox), this->tabla, FALSE, FALSE, 0);
		//La muestro y dibujo el mapa
		gtk_widget_show(this->tabla);
		this->dibujar_mapa();
	}
}

//Dibujar Mapa:

void VistaMapa::dibujar_mapa() {
	int cont1 = 0; int cont2 = 0;
	Mapa* mapa = this->nivel->get_mapa();
	//Recorro todo el mapa del nivel actual
	while (cont1 < mapa->get_alto()){
		while (cont2 < mapa->get_ancho()){
			//Obtengo cada casillero, y los elementos del mismo
			S_ptr<Casillero> casillero = mapa->get_casillero(cont1, cont2);
			S_ptr<Elemento> estruct = casillero->get_estructural();
			S_ptr<Elemento> modificador = casillero->get_modificador();
			//Si hay estructural, es porque puede haber estructural y modif o estruc solo
			if (!estruct.es_nulo()){
				//Si es la primera vez que veo al estructural lo grafico
				if ((estruct->get_pos_x() == cont1) && (estruct->get_pos_y() == cont2))
					this->dibujar_elemento(estruct);
				//Si tiene un modificador lo grafico
				if (!modificador.es_nulo())
					this->dibujar_elemento(modificador);
			} else { //Si no hay estructural grafico un casillero vacio
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
		GtkWidget* fixed; //GTK Fixed para contener la imagen del estructural y de los modificadores a la vez
		GtkWidget* imagenEstruc;
		GtkWidget* imagenModif;
		//Obtengo las posiciones del elemento
		int pos_x = elem->get_pos_x();
		int pos_y = elem->get_pos_y();
		//Si es un estructural
		if (elem->es_estructural()){
			//Creo un nuevo fixed, y la imagen del estructural traida desde el archivo.
			fixed = gtk_fixed_new();
			imagenEstruc = gtk_image_new();
			gtk_image_set_from_file(GTK_IMAGE(imagenEstruc), elem->get_ruta_imagen());
			//Pongo la imagen en el fixed, en las posiciones 0,0
			gtk_fixed_put(GTK_FIXED(fixed), imagenEstruc, 0, 0);
			//Agrego el fixed a la tabla segun el tamaño del estructural
			gtk_table_attach_defaults (GTK_TABLE (this->tabla), fixed, pos_y, pos_y + elem->get_ancho(), pos_x, pos_x + elem->get_alto());
			//Agrego en la matriz de imagenes la referencia al fixed
			for (int i = pos_x; i < pos_x + elem->get_alto(); i++)
				for (int j = pos_y; j < pos_y + elem->get_ancho(); j++)
					this->imagenes[i][j] = fixed;
		} else {
			//Si es un modificador obtengo el estructural, el fixed en esa pos, y creo la imagen del modif desde un archivo
			S_ptr<Elemento> estruct = this->nivel->get_mapa()->get_casillero(pos_x, pos_y)->get_estructural();
			fixed = this->imagenes[pos_x][pos_y];
			imagenModif = gtk_image_new();
			gtk_image_set_from_file(GTK_IMAGE(imagenModif), elem->get_ruta_imagen());
			//Pongo la imagen del modif en el fixed en las coordenadas relativas al mismo, utilizando las posiciones del estructural
			gtk_fixed_put(GTK_FIXED(fixed), imagenModif, (pos_y - estruct->get_pos_y()) * 25, (pos_x - estruct->get_pos_x()) * 25);			
			//Agrego en la matriz de imagenes de modificadores al nuevo modif
			this->imag_modif[pos_x][pos_y] = imagenModif;
			//Si el modificador se agrega en la primera pos del estructural y habia una cruz, renuevo esta
			//ultima para que quede por sobre todo lo demas
			if ((pos_x == estruct->get_pos_x()) && (pos_y == estruct->get_pos_y()) && (this->marcas[estruct->get_pos_x()][estruct->get_pos_y()] != NULL)) {
					this->desmarcar_elemento(pos_x, pos_y);
					this->marcar_elemento(pos_x, pos_y);
			}
		}
		//Muestro los elementos agregados
		gtk_widget_show_all(fixed);
}

/* Dibujar Casillero Vacio: */

void VistaMapa::dibujar_casillero_vacio(int pos_x, int pos_y){
		//Creo una imagen con la ruta del casillero vacio
		GtkWidget* imagen;
		imagen = gtk_image_new();
		gtk_image_set_from_pixbuf(GTK_IMAGE(imagen), this->pixbuf_vacio);
		//Agrego a la tabla en las pos pasadas por parametro y lo agrego tmb a la matriz de referencias a imagenes
		gtk_table_attach_defaults (GTK_TABLE (this->tabla), imagen, pos_y, pos_y + 1, pos_x, pos_x + 1);
		this->imagenes[pos_x][pos_y] = imagen;
		gtk_widget_show(imagen); //Muestro la imagen
}

/* Borrar Elemento: */

void VistaMapa::borrar_elemento(S_ptr<Elemento> elem){
		if (!elem.es_nulo()){
			//Obtengo las coords del elemento
			int pos_x = elem->get_pos_x();
			int pos_y = elem->get_pos_y();
			//Si es un estructural
			if (elem->es_estructural()) {
				//Obtengo su tamaño
				int alto = elem->get_alto();
				int ancho = elem->get_ancho();
				//Remuevo el fixed de la tabla junto con todas las imagenes de los modificadores
				gtk_container_remove(GTK_CONTAINER(this->tabla), imagenes[pos_x][pos_y]);
				//Remuevo de las matrices todas las referencias a las imagenes de estructurales y modificadores
				//teniendo en cuenta la posicion del estructural y su tamaño
				for (int i = pos_x; i < pos_x + alto; i++)
					for (int j = pos_y; j < pos_y + ancho; j++){
						this->imagenes[i][j] = NULL;
						this->imag_modif[i][j] = NULL;
					}
			} else {
				//Si es un modificador remuevo la imagen del mismo del fixed adecuado, y tmb de la matriz de referencias
				//a imagenes de modificadores
				GtkWidget* fixed = this->imagenes[pos_x][pos_y];
				gtk_container_remove(GTK_CONTAINER(fixed), imag_modif[pos_x][pos_y]);
				imag_modif[pos_x][pos_y] = NULL;
			}
		}
}

/* Borrar Casillero Vacio: */

void VistaMapa::borrar_casillero_vacio(int pos_x, int pos_y){
		//Remuevo la imagen que se encuentra en las pos pasadas por parameto de la tabla, y tmb de la matriz de ref.
		if (imagenes[pos_x][pos_y] != NULL){
			gtk_container_remove(GTK_CONTAINER(this->tabla), imagenes[pos_x][pos_y]);
			this->imagenes[pos_x][pos_y] = NULL;
		}
}

/* Agregar Elemento: */

void VistaMapa::agregar_elemento(int pos_x, int pos_y){
	
	//Me fijo en el control de seleccion el tipo y orientacion de la ficha seleccionada
	TipoElem tipo = ControlSeleccion::get_instance()->get_tipo_selec();
	Orientacion orientacion = ControlSeleccion::get_instance()->get_orientacion_selec();
	//Intento agregar al nivel una ficha con esos datos
	if (this->nivel->agregar_elemento(tipo, pos_x, pos_y, orientacion)){
		//Si se pudo agregar, grafico el elemento agregado
		S_ptr<Casillero> casillero = this->nivel->get_mapa()->get_casillero(pos_x, pos_y);
		S_ptr<Elemento> elem = casillero->get_modificador();
		if (!casillero->tiene_modificador()){
			//Si se agrega un estructural primero borro la superficie necesaria en la tabla
			elem = casillero->get_estructural();
			for (int i = elem->get_pos_x(); i < elem->get_pos_x() + elem->get_alto(); i++)
				for (int j = elem->get_pos_y(); j < elem->get_pos_y() + elem->get_ancho(); j++)
					this->borrar_casillero_vacio(i, j);
		}
		this->dibujar_elemento(elem);
		//Aviso que hay un elemento nuevo y mando el nivel
		this->set_cambio();
		this->avisar_observadores(&this->nivel);
	}
}

/* Quitar Elemento: */

void VistaMapa::quitar_elemento(int pos_x, int pos_y){
	
	//Me fijo si donde se hizo click hay algun casillero
	S_ptr<Casillero> casillero = this->nivel->get_mapa()->get_casillero(pos_x, pos_y);
	if (!casillero.es_nulo()){
		//Si lo hay obtengo su elemento, priorizando el modificador
		S_ptr<Elemento> elem = casillero->get_estructural();
		
		if (casillero->tiene_modificador())
			elem = casillero->get_modificador();
		//Intento quitar al elemento del mapa
		if ((!elem.es_nulo()) && (this->nivel->quitar_elemento(pos_x, pos_y))){
			//Si se pudo quitar, borro el elemento de la parte grafica y si es estructural relleno
			//con casilleros vacios
			this->borrar_elemento(elem);
			if (elem->es_estructural())
				for (int i = elem->get_pos_x(); i < elem->get_pos_x() + elem->get_alto(); i++)
					for (int j = elem->get_pos_y(); j < elem->get_pos_y() + elem->get_ancho(); j++)
						this->dibujar_casillero_vacio(i,j);
			//Aviso que se quito un elemento y mando el nivel
			this->set_cambio();
			this->avisar_observadores(&this->nivel);
		}
	}
}

/* Marcar Elemento: */

void VistaMapa::marcar_elemento(int pos_x, int pos_y){
	//Si hay un elemento y no estaba marcado
	if ((this->imagenes[pos_x][pos_y] != NULL) && (this->marcas[pos_x][pos_y] == NULL)){
		//Creo una imagen con la ruta de la marca
		GtkWidget* imagen;
		imagen = gtk_image_new();
		gtk_image_set_from_pixbuf(GTK_IMAGE(imagen), this->pixbuf_marca);
		this->marcas[pos_x][pos_y] = imagen;
		GtkWidget* fixed = this->imagenes[pos_x][pos_y];
		//Pongo la imagen de la marca en el fixed, en el (0,0)
		gtk_fixed_put(GTK_FIXED(fixed), imagen, 0, 0);				
		gtk_widget_show_all(fixed); //Muestro la el fixed otra vez
	}
}
	
/* Desmarcar Elemento: */

void VistaMapa::desmarcar_elemento(int pos_x, int pos_y){
	//Si hay un elemento y estaba marcado
	if ((this->imagenes[pos_x][pos_y] != NULL) && (this->marcas[pos_x][pos_y] != NULL)){
		//Obtengo la imagen del elemento y la marca y saco la marca del elemento
		GtkWidget* imagen = this->marcas[pos_x][pos_y];
		GtkWidget* fixed = this->imagenes[pos_x][pos_y];
		gtk_container_remove(GTK_CONTAINER(fixed), imagen);
		this->marcas[pos_x][pos_y] = NULL;
		gtk_widget_show_all(fixed); //Muestro el fixed otra vez
	}
}

/* Click Handler: */

gboolean VistaMapa::click_handler (GtkWidget      *widget, 
					 GdkEventButton *event,
					 gpointer        data)
{
	
	VistaMapa* vista_mapa = (VistaMapa*) data;
	//Si el nivel actual no es nulo
	if (!(vista_mapa->nivel).es_nulo()) {
		
		//Obtengo el corrimiento de los scrolls
		GtkAdjustment* adjh = gtk_scrolled_window_get_hadjustment(GTK_SCROLLED_WINDOW(vista_mapa->swindow));
		GtkAdjustment* adjv = gtk_scrolled_window_get_vadjustment(GTK_SCROLLED_WINDOW(vista_mapa->swindow));
	
		//Obtengo las posiciones x e y arregladas segun las pasadas por parametro, el tam del casillero y los corrimientos
		int pos_y = (int) ((event->x + gtk_adjustment_get_value(adjh)) / 25);
		int pos_x = (int) ((event->y + gtk_adjustment_get_value(adjv)) / 25);
	
		//Si se apreta click izq llamo al agregar, sino al quitar ficha
		if (event->button == 1)
			vista_mapa->agregar_elemento(pos_x, pos_y);
		else
			vista_mapa->quitar_elemento(pos_x, pos_y);
	}
	
	return TRUE;
}
