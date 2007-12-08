//HEADER

#ifndef FILE_CHOOSER_H_
#define FILE_CHOOSER_H_

#include "modelo.h"
#include "gui.h"
#include <gtk/gtk.h>

/* CLASE FILE CHOOSER: Permite guardar y cargar archivos de mundos, con extension xml. */

class FileChooser {

  private:
	  GtkWidget* file_chooser; //Widget que representa al file chooser
	  GtkFileFilter* filtro_xml; //Contiene el filtro para extension xml.
  	  GtkFileChooserAction accion; //Accion a realizar por el file chooser: guardar o cargar.
  
  public:

	/* Constructor: Crea el file chooser y lo inicializa, con el titulo pasado por parametro y como hijo
  	   de la ventana pasada por parametro. Se debe pasar el tipo de accion por parametro: 
	   GTK_FILE_CHOOSER_ACTION_SAVE para guardar o GTK_FILE_CHOOSER_ACTION_OPEN para cargar.*/
	FileChooser(char* titulo, GtkWidget* window, GtkFileChooserAction accion);
  
  	/* Destructor: Libera los recursos consumidos por el file chooser */
    ~FileChooser();
  
  	/* Ejecutar: Ejecuta la ventana de dialogo del file chooser hasta que el usuario presiona un boton,
  	   en cuyo caso se interrumpe y realiza la accion adecuada. */
  	void ejecutar();
  
    /* Get Widget: Devuelve la representacion del file chooser como widget */
	GtkWidget* get_widget();
  
  	/* Get FileName: Devuelve el nombre del archivo seleccionado */
  	char* get_filename();
  
  private:
	  
  	/* Cumple Filtro: Devuelve true si el filename del file chooser cumple con el filtro xml, false
  	   en caso contrario. */
  	bool cumple_filtro();
  
  	/* Mostrar Msg: Muestra el mensaje pasado por parametro por una ventana de dialogo */
  	void mostrar_msg(char* msg);
  
};

#endif