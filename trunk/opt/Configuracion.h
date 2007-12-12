#ifndef __CONFIGURACION_H__
#define __CONFIGURACION_H__

#include <map>
#include <string>
#include "ConfValue.h"

class Configuracion
{
	private:
		typedef std::map<std::string, ConfValue> Mapa;

		Mapa confs;

	public:
		void set_conf( std::string nom, ConfValue v );

		ConfValue get_conf( std::string nom );

		void load_conf( std::string ruta );
};

#endif
