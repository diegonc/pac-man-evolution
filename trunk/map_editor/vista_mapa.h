//HEADER

#ifndef VISTA_MAPA_H
#define VISTA_MAPA_H

#include <gtk/gtk.h>
#include "elemento.h"
#include "nivel.h"
#include "definiciones.h"
#include "control_seleccion.h"
#include "../common/smart_pointer.h"

/* CLASE VISTA_MAPA: Clase que representa la interfaz grafica del mapa en el editor. */

class VistaMapa {
   
   private:

	GtkWidget* frame; //Marco con titulo
   	GtkWidget* swindow; //Scrolled window para poder scrollear el mapa
	GtkWidget* tabla; //Tabla que contiene los casilleros del mapa
    GtkWidget*** imagenes; //Matriz de imagenes contenidas en la tabla
    S_ptr<Nivel> nivel; //Nivel que contiene el mapa a representar
   
   public:

	//Constructor: Genera la vista del mapa segun el tamaño del nivel y lo grafica.
	VistaMapa(S_ptr<Nivel> nivel);
   
   	//Destructor: Libera los recursos consumidos por la vista del mapa.
    ~VistaMapa();

	//Get Widget: Obtiene la representacion del mapa como widget.
	GtkWidget* get_widget() const;
   
   	//Dibujar: Recorre todos los casilleros del mapa y los dibuja segun su contenido.
    void dibujar();
   
   private:
	   
   /* Dibujar Elemento: Dibuja el elemento pasado por parametro en el mapa, segun sus posiciones y su tamanio. */

	void dibujar_elemento(S_ptr<Elemento> elem);
	
	/* Dibujar Casillero Vacio: Dibuja un casillero vacio en las posiciones pasadas por parametro. */
	
	void dibujar_casillero_vacio(int pos_x, int pos_y);
   
   /* Borrar Elemento: Quita la imagen del elemento pasado por parametro del mapa. */

	void borrar_elemento(S_ptr<Elemento> elem);
   
   /* Borrar Casillero Vacio: Quita la imagen del casillero en blanco en las pos x, y*/

	void borrar_casillero_vacio(int pos_x, int pos_y);
   
   /* Agregar Elemento: Agrega un nuevo elemento en las posiciones x,y */

	void agregar_elemento(double posX, double posY);
   
   /* Quitar Elemento: Quita el elemento que se encuentra en las posiciones x,y */

	void quitar_elemento(double posX, double posY);

   	/* Click Handler: Se encarga de realizar una accion cuando se clickea al mapa
   	   en una posicion determinada */
   
   	static gboolean click_handler (GtkWidget *widget, GdkEventButton *event, gpointer data);
   
};

#endif
