#include "ConfCliente.h"
#include <stdexcept>
#include <fstream>

ConfCliente::ConfCliente( int argc, char** argv )
{
	validar_linea_comando( argc, argv );
	cargar_configuracion( argv[1] );
}

void ConfCliente::validar_linea_comando(int argc, char** argv)
{
	if( argc != 2 ) {
		throw std::runtime_error(
"Numero incorrecto de parametros.\n"
"Uso de la aplicacion:\n"
"\tpme-client archivo\n\n"
"\t\tarchivo\t\tRuta al archivo de configuracion.\n\n"
"Para conocer la sintaxis del archivo de configuracion vea la configuracion de "
"ejemplo en el archivo 'sample.conf'." );
	} else {
		std::ifstream ifs( argv[1] );

		if( ! ifs.is_open() ) {
			std::string s("Error abriendo archivo para lectura: ");
			s += argv[1];
			s += "\nVerifique la ruta y los permisos del archivo.";
			throw std::runtime_error(s);
		}
	}
}

void ConfCliente::cargar_configuracion(char* archivo)
{
	// Se agregan las opciones del archivo de configuracion.
	conf.load_conf( archivo );
}

std::string ConfCliente::get_direccion()
{
	try {
		ConfValue cv = conf.get_conf( "direccion" );
		return cv.get_texto();
	}catch( ... ) { /* TODO: ajustar excepcion." */
		throw std::runtime_error( "Establezca la opcion 'direccion' con la direccion de la maquina servidor." );
	}
}

unsigned int ConfCliente::get_puerto()
{
	try {
		ConfValue cv = conf.get_conf( "puerto" );
		return cv.get_numero();
	}catch( ... ) { /* TODO: ajustar excepcion." */
		throw std::runtime_error( "Establezca la opcion 'puerto' con el puerto en el que el servidor debe escuchar en el archivo de configuracion." );
	}
}
