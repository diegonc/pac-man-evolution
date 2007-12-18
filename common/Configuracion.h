#ifndef __CONFIGURACION_H__
#define __CONFIGURACION_H__

#include <map>
#include <iostream>
#include <string>
#include "ConfValue.h"

class Configuracion
{
	private:
		typedef std::map<std::string, ConfValue> Mapa;

		Mapa confs;

	public:
		void set_conf( std::string nom, ConfValue v );

		ConfValue get_conf( std::string nom ) const;

		void load_conf( std::string ruta );

		bool operator==( const Configuracion& otro ) const;

		void dump( std::ostream& out ) const;
};

#endif
