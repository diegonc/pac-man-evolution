//HEADER

#ifndef FILE_CHOOSER_H_
#define FILE_CHOOSER_H_

#include "app_editor.h"
#include <gtk/gtk.h>

/* CLASE FILE CHOOSER: Permite guardar y cargar archivos xml de mundos. */

class FileChooser {

  private:
	  GtkWidget* file_chooser; //Widget que representa al file chooser
	  GtkFileFilter* filtro_mundo; //Contiene el filtro para la extension del mundo.
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
  
};

#endif
