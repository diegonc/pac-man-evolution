#ifndef __APP_H__
#define __APP_H__

/**
*	@brief
*
*	-	Esta clase es la que modela la aplicacion. 
*	-	Solo se permite una unica instancia. 
*	-	Implementada con smart_pointer como tecnica RAII
*/

#include <common/smart_pointer.h>
#include <common/Configuracion.h>

class App{
	private:
		App(int argc, char *argv[]);
		App(App& a);
	
		static S_ptr<App> instancia;
		
		int argc;
		char **argv;

		Configuracion conf;


		void validar_linea_comando();

		void cargar_configuracion();

		std::string get_mundo_xml();

		unsigned int get_puerto_servidor();

		unsigned int get_cl_min();

		unsigned int get_cl_max();

	public:
		~App();
		
		/** @brief Permite obtener la unica instancia de la clase
		 *
		 *  @return Un smart pointer que contiene el la instancia de App
		 */	

		static S_ptr<App> get_instancia(int argc, char *argv[]);
	
		/** @brief Ejecuta la aplicacion
		 *
		 *  @return el codigo de salida conteniendo el resultado de la aplicacion
		 */
		int ejecutar();		
};

#endif /* __APP_H__ */
