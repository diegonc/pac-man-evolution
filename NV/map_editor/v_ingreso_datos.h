//HEADER

#ifndef V_INGRESO_DATOS_H_
#define V_INGRESO_DATOS_H_

#include <gtk/gtk.h>
#include <stdlib.h>
#include <string>
#include "gui.h"
#include "modelo.h"

using namespace std;

/* CLASE VIngDatos: Clase que se encarga de controlar el ingreso de los datos para un nuevo nivel. */

class VIngDatos {

  private:
	  GtkWidget* dialogo; //Widget que representa a la ventana de dialogo de ingreso de datos
	  GtkWidget* entrada_nombre; //Widget que representa una caja para el ingreso del nombre
  	  GtkWidget* entrada_ancho; //Widget que representa una caja para el ingreso del ancho del nivel
  	  GtkWidget* entrada_alto; //Widget que representa una caja para el ingreso del alto del nivel
  	  string nombre; //Nombre de nivel ingresado
  	  int alto; //Alto de nivel ingresado
  	  int ancho; //Ancho de nivel ingresado
  
  public:

	/* Constructor: Crea la ventana de ingreso de nombres, con el titulo y y como hija
  	   de la ventana pasada por parametro. */
	VIngDatos(char* titulo, GtkWidget* window);
  
  	/* Destructor: Libera los recursos consumidos por la ventana */
    ~VIngDatos();
  
  	/* Ejecutar: Ejecuta la ventana de dialogo hasta que el usuario presiona un boton,
  	   en cuyo caso se interrumpe. 
  	   Si alguno de los datos ingresados es invalido o se apreto cancela devuelve false.
  	   Caso contrario devuelve true.*/
  	bool ejecutar();
  
    /* Get Widget: Devuelve la representacion de la ventana como widget. */
	GtkWidget* get_widget();
  
  	/* Get Nombre: Devuelve el nombre de nivel ingresado por el usuario. */
  	string get_nombre();
  
  	/* Get Alto: Devuelve el alto del nivel ingresado por el usuario. */
  	int get_alto();
  
  	/* Get Ancho: Devuelve el ancho del nivel ingresado por el usuario. */
  	int get_ancho();
  
};

#endif
