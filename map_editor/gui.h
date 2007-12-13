//HEADER

#ifndef GUI_H_
#define GUI_H_

#include <gtk/gtk.h>
#include "definiciones.h"
#include "../common/thread.h"
#include "v_principal.h"

class VPrincipal;

/* CLASE GUI: Representa la interfaz grafica de usuario del editor.
   Corre sobre un hilo propio de ejecucion, en el cual espera eventos. */

class GUI : public Thread {
   
   private:

	VPrincipal* ventana; //Referencia a la ventana principal del GUI
   
   	static GUI* instancia; //Referencia a la unica instancia del gui
   
   private:

	//Constructor: Generea la interfaz grafica del editor. Recibe como parametros los parametros de invocacion del programa.

	GUI(int &argc, char** &argv);
   
   	/* Pongo al constructor de copia como privado para que no se pueda copiar al singleton */
	GUI(const GUI &gui){}

	//Destructor: Libera los recursos consumidos por la interfaz grafica
	~GUI();
   
   public:
	   
   	/* Get Instance: Devuelve la unica instancia de la GUI. Si no existe la crea.
		   Para ello recibe los parametros necesarios para la creacion.
		   argc->Cantidad de parametros de invocacion
		   argv->Vector de parametros de invocacion		   */
	static GUI* get_instance(int argc, char* argv[]);

	/* Run: El hilo de GUI se queda esperando eventos, hasta que que se recibe uno del tipo delete_event 
   	   y corta la ejecucion, liberando la memoria consumida. */
	virtual void run();
   
	/* Destroy: Se encarga de liberar los recursos consumidos por el GUI */
	static void destroy();
   
   	/* Get Ventana Principal: Devuelve una referencia a la ventana principal del programa. */
   	VPrincipal* get_ventana_principal();
	
};

#endif
