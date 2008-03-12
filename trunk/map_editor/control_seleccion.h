//Header
#ifndef Control_Seleccion_h_
#define Control_Seleccion_h_

//Incluyo las librerias necesarias
#include <editor/definiciones.h>
#include <common/observador.h>
#include <common/smart_pointer.h>
#include "item_elem.h"

using namespace std;

/* CLASE CONTROL SELECCION: Clase singleton que se encarga de controlar cual es el ultimo item
   que ha sido seleccionado en cualquiera de los paneles de elementos. */

class ControlSeleccion : public Observador {

	//Atributos
	private:
		S_ptr<ItemElem> item_seleccionado;
		
		static ControlSeleccion* instancia; //Referencia a la unica instancia del controlador
		
		/* Constructor Privado: Inicializa el controlador de seleccion con seleccion nula. */
		ControlSeleccion();
	
		/* Destructor Privado: Libera la memoria reservada por el controlador */
		~ControlSeleccion();
	
	public:
		
		/* Get Instance: Devuelve la unica instancia del controlador. Si no existe la crea. */
		static ControlSeleccion* get_instance();
	
		//Get Tipo Selec: Devuelve el tipo del elemento seleccionado.
   		TipoElem get_tipo_selec();
   
   		//Get Orientacion Selec: Devuelve la orientacion del elemento seleccionado.
   		Orientacion get_orientacion_selec();
		
		//Actualizar: Actualiza la seleccion cuando se produce algun cambio en algun panel de elementos */
		virtual void actualizar(Observable * observable, void * param);
	
		/* Destroy: Se encarga de liberar los recursos consumidos por el controlador. */
		static void destroy();
	
};

#endif
