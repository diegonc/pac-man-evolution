//HEADER

#ifndef VISTA_MAPA_H
#define VISTA_MAPA_H

#include <gtk/gtk.h>
#include "elemento.h"
#include "nivel.h"
#include "definiciones.h"
#include "../common/smart_pointer.h"

/* CLASE VISTA_MAPA: Clase que representa la interfaz grafica del mapa en el editor. */

class VistaMapa {
   
   private:

	GtkWidget* frame; //Marco con titulo
   	GtkWidget* swindow; //Scrolled window para poder scrollear el mapa
	GtkWidget* tabla; //Tabla que contiene los casilleros del mapa
    S_ptr<Nivel> nivel; //Nivel que contiene el mapa a representar
   
   public:

	//Constructor: Genera la vista del mapa segun el tamaño del nivel y lo grafica.
	VistaMapa(S_ptr<Nivel> nivel);

	//Get Widget: Obtiene la representacion del mapa como widget.
	GtkWidget* get_widget() const;
   
   	//Dibujar: Recorre todos los casilleros del mapa y los dibuja segun su contenido.
    void dibujar();
};

#endif
