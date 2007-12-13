//HEADER

#ifndef VISTA_MAPA_H
#define VISTA_MAPA_H

#include <gtk/gtk.h>
#include "elemento.h"
#include "nivel.h"
#include "definiciones.h"
#include "control_seleccion.h"
#include "act_marcas.h"
#include "../common/smart_pointer.h"
#include "../common/observable.h"
#include "../common/observador.h"

class ActualizadorMarcas;

/* CLASE VISTA_MAPA: Clase que representa la interfaz grafica del mapa en el editor. 
   Observa al panel de niveles para saber cuando cambiar de nivel. */

class VistaMapa : public Observador, public Observable {
   
   private:

	GtkWidget* frame; //Marco con titulo
   	GtkWidget* swindow; //Scrolled window para poder scrollear el mapa
	GtkWidget* tabla; //Tabla que contiene los casilleros del mapa
    GtkWidget*** imagenes; //Matriz de imagenes contenidas en la tabla (conjunto estruct + modif)
   	GtkWidget*** imag_modif; //Matriz de imagenes de modificadores contenidos en la tabla
   	GtkWidget*** marcas; //Matriz que contiene las referencias a las imagenes con las marcas de los casilleros desconectados
   	GtkWidget* vbox; //Widget de uso interno
   	GtkWidget* hbox; //Widget de uso interno
    S_ptr<Nivel> nivel; //Nivel que contiene el mapa a representar
   
    GdkPixbuf* pixbuf_vacio; //Pixbuf donde almaceno la imagen de un casillero vacio para tenerlo cargado una sola vez
    GdkPixbuf* pixbuf_marca;   //Pixbuf donde almaceno la imagen de la marca, para tenerla cargada una sola vez
    ActualizadorMarcas* actualizador; //Referencia al actualizador de marcas, que se encarga de dibujar las marcas en los elems desc
   
   public:

	//Constructor: Genera la vista del mapa.
	VistaMapa();
   
   	//Destructor: Libera los recursos consumidos por la vista del mapa.
    ~VistaMapa();

	//Get Widget: Obtiene la representacion del mapa como widget.
	GtkWidget* get_widget() const;
   
   	//Actualizar: Redibuja el mapa cuando la seleccion de nivel cambia.
	virtual void actualizar(Observable * observable, void * param);
   
    /* Agregar Elemento: Agrega un nuevo elemento en el casillero que se encuentra en
	   pos_x, pos_y. El elemento que se agrega es el que actualmente se encuentra seleccionado
   	   en los paneles de elementos.*/
	void agregar_elemento(int pos_x, int pos_y);
   
   	/* Quitar Elemento: Quita el elemento que se encuentra en el casillero pos_x, pos_y */
	void quitar_elemento(int pos_x, int pos_y);
   
   	/* Marcar Elemento: Agrega al elemento que se encuentra en el casillero pos_x, pos_y una
	   marca con una cruz. */
	void marcar_elemento(int pos_x, int pos_y);
	
	/* Desmarcar Elemento: Quita la marca del elemento que se encuentra en el casillero pos_x, pos_y,
	   si este se encontraba marcado. */
	void desmarcar_elemento(int pos_x, int pos_y);
   
   private:
	   
  	//Inicializar Matriz: Crea e inicializa la matriz de widgets pasada por parametro con NULL.
    void inicializar_matriz(GtkWidget*** &matriz);
   
   	//Liberar Matriz: Libera la memoria consumida por la matriz de widgets pasada por parametro.
   	void liberar_matriz(GtkWidget*** &matriz);
	
    //Redibujar: Redibuja el mapa con el contenido del nivel pasado por parametro
    void redibujar(S_ptr<Nivel> nivel);
   
    //Dibujar Mapa: Recorre todos los casilleros del mapa y los dibuja segun su contenido.
    void dibujar_mapa();
	   
   /* Dibujar Elemento: Dibuja el elemento pasado por parametro en el mapa, segun sus posiciones y su tamanio. */
	void dibujar_elemento(S_ptr<Elemento> elem);
	
	/* Dibujar Casillero Vacio: Dibuja un casillero vacio en las posiciones pasadas por parametro. */
	void dibujar_casillero_vacio(int pos_x, int pos_y);
   
   /* Borrar Elemento: Quita la imagen del elemento pasado por parametro del mapa. */
	void borrar_elemento(S_ptr<Elemento> elem);
   
   /* Borrar Casillero Vacio: Quita la imagen del casillero en blanco en las pos x, y*/
	void borrar_casillero_vacio(int pos_x, int pos_y);

   	/* Click Handler: Se encarga de realizar una accion cuando se clickea al mapa
   	   en una posicion determinada */
   	static gboolean click_handler (GtkWidget *widget, GdkEventButton *event, gpointer data);
   
};

#endif
