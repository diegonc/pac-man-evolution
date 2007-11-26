//Header
#ifndef App_h_
#define App_h_

//Incluyo las librerias necesarias
#include "gui.h"

using namespace std;

/* CLASE APP: Esta clase representa a la aplicacion en si. Tiene
   una sola instancia y un punto de acceso global a ella. */

class App {

	//Atributos
	private:
		GUI* gui; //Referencia a la interfaz grafica del usuario
		Modelo* modelo; //Referencia al modelo que contiene la logica de la app
		
		static App* instancia; //Referencia a la unica instancia del programa
		
		/* Constructor Privado: Inicializa la aplicacion. Recibe el vector y la cantidad
                   de argumentos por parametro.
                   argc->Cantidad de parametros de invocacion
                   argv->Vector de parametros de invocacion	 */
		App(int argc, char* argv[]);
	
		/* Destructor Privado: Libera la memoria reservada por la aplicacion */
		~App();
		
		/* Imprimir error: Segun el codigo de error pasado por parametro, imprime el mensaje
		   por stderr. Si no lo reconoce no hace nada. */
		void imprimir_error(int error);	
	
	public:
		
		/* Get Instance: Devuelve la unica instancia del programa. Si no existe la crea.
		   Para ello recibe los parametros necesarios para la creacion.
		   argc->Cantidad de parametros de invocacion
		   argv->Vector de parametros de invocacion		   */
		static App* get_instance(int argc, char* argv[]);
	
		/* Ejecutar: Ejecuta la aplicacion. Devuelve el codigo de error */
		int ejecutar();
	
		/* Destroy: Se encarga de liberar los recursos consumidos por la aplicacion */
		static void destroy();
	
};

#endif
