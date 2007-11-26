//HEADER

#ifndef GUI_H_
#define GUI_H_

#include <gtk/gtk.h>
#include "definiciones.h"
#include "../common/thread.h"
#include "v_principal.h"

/* CLASE GUI: Representa la interfaz grafica de usuario del editor.
   Corre sobre un hilo propio de ejecucion, en el cual espera eventos. */

class GUI : public Thread {
   
   private:

	VPrincipal* ventana; //Referencia a la ventana principal del GUI
   
   public:

	//Constructor: Generea la interfaz grafica del editor. Recibe como parametros los parametros de invocacion del programa.

	GUI(int &argc, char** &argv);

	//Destructor: Libera los recursos consumidos por la interfaz grafica
	~GUI();

	/* Run: El hilo de GUI se queda esperando eventos, hasta que recibe uno del tipo delete_event y corta la ejecucion, liberando la memoria consumida. */
	
	virtual void run();
	
};

#endif
