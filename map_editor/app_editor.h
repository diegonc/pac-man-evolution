//Header
#ifndef App_Editor_h_
#define App_Editor_h_

//Incluyo las librerias necesarias
#include "gui.h"

using namespace std;

/* CLASE APP EDITOR: Esta clase representa a la aplicacion en si. Tiene
   una sola instancia y un punto de acceso global a ella. */

class AppEditor {

	//Atributos
	private:
		GUI* gui; //Referencia a la interfaz grafica del usuario
		Modelo* modelo; //Referencia al modelo que contiene la logica de la app
		
		static AppEditor* instancia; //Referencia a la unica instancia del programa
		
		/* Constructor Privado: Inicializa la aplicacion. Recibe el vector y la cantidad
                   de argumentos por parametro.
                   argc->Cantidad de parametros de invocacion
                   argv->Vector de parametros de invocacion	 */
		AppEditor(int argc, char* argv[]);
	
		/* Destructor Privado: Libera la memoria reservada por la aplicacion */
		~AppEditor();
		
	public:
		
		/* Get Instance: Devuelve la unica instancia del programa. Si no existe la crea.
		   Para ello recibe los parametros necesarios para la creacion.
		   argc->Cantidad de parametros de invocacion
		   argv->Vector de parametros de invocacion		   */
		static AppEditor* get_instance(int argc, char* argv[]);
	
		/* Ejecutar: Ejecuta la aplicacion. */
		void ejecutar();
	
		/* Destroy: Se encarga de liberar los recursos consumidos por la aplicacion */
		static void destroy();
	
};

#endif
