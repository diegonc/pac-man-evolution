#ifndef CONF_CLIENTE_H__
#define CONF_CLIENTE_H__

#include <common/Configuracion.h>

class ConfCliente
{
	Configuracion conf;

	void validar_linea_comando(int argc, char** argv);

	void cargar_configuracion(char* archivo);

	public:
		ConfCliente( int argc, char** argv );

		std::string get_direccion();

		unsigned int get_puerto();
};

#endif
