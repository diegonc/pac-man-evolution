
#include "Configuracion.h"
#include <fstream>
#include <sstream>

void Configuracion::set_conf( std::string nom, ConfValue v )
{
	confs[ nom ] = v;	
}

ConfValue Configuracion::get_conf( std::string nom )
{
	Mapa::iterator it = confs.find( nom );
	if( it != confs.end() )
		return (*it).second;
	throw "TODO: nombre de opcion no disponible.";
}

void Configuracion::load_conf( std::string ruta )
{
	std::ifstream file( ruta.c_str() );
	std::string identificador;
	std::string tmpbuf;
	ConfValue valor;
	char c;

	#define E_LEYENDO	0 /* Esperando token. */
	#define E_COMENTARIO	1 /* Comentario encontrado. */
	#define E_IDENTIFICADOR 2 /* Identificador encontrado */
	#define E_VALOR		3 /* Esperando valor. */
	#define E_CADENA	4 /* Inicio de cadena encontrado. */
	#define E_NUMERO	5 /* Numero encontrado. */
	#define E_BOOL		6 /* Booleano encontrado. */
	#define E_REG_CADENA	7 /* Fin de cadena encontrado. */
	#define E_REG_NUMERO	8 /* Fin de numero encontrado. */
	#define E_REG_BOOL	9 /* Fin de numero encontrado. */

	int estado = E_LEYENDO;

	while( file.good() ) {
		file.get(c);
		switch( estado ) {
			case E_LEYENDO:
				if( c == '#' ) estado = E_COMENTARIO;
				else if( c != ' ' && c != '\t' && c != '\n' ) {
					file.unget();
					estado = E_IDENTIFICADOR;
					identificador = "";
				}
				break;
			case E_COMENTARIO:
				while( file.ignore().good() );
				estado = E_LEYENDO;
				break;
			case E_IDENTIFICADOR:
				if( c == '=' || c == ':' )
					estado = E_VALOR;
				else if( c != ' ' && c != '\t' && c != '\n' )
					identificador += c;
				else if( c == '\n' || c == '#' ) {
					/* TODO: error en archivo. */
					file.unget();
					estado = E_COMENTARIO;
				}
				break;
			case E_VALOR:
				if( c == '\"' ) {
					tmpbuf = "";
					estado = E_CADENA;
				} else if (  c >= '0' && c <= '9' ) {
					tmpbuf = "";
					file.unget();
					estado = E_NUMERO;
				} else if ( c == 't' || c == 'f' ) {
					tmpbuf = "";
					file.unget();
					estado = E_BOOL;
				} else if( c != ' ' && c != '\t'  ) {
					/* TODO: error en archivo. */
					file.unget();
					estado = E_COMENTARIO;
				} 
				break;
			case E_CADENA:
				if( c == '\n' ) {
					/* TODO: error en archivo. */
					file.unget();
					estado = E_COMENTARIO;
				} else if( c == '\"' ) {
					/* fin de cadena. */
					estado = E_REG_CADENA;
				} else /* agrega al valor el caracter leido. */
					tmpbuf += c;
				break;
			case E_NUMERO:
				if( c == '\n' || c == ' ' || c == '\t' ) {
					/* fin de numero. */
					file.unget();
					estado = E_REG_NUMERO;
				} else if( c >= '0' && c <= '9' ) {
					/* agrega digitos. */
					tmpbuf += c;
				} else {
					/* TODO: error, basura al final del
					 * numero. Por ahora, somos gentiles y
					 * usamos los digitos que se han leido.
					 */
					estado = E_REG_NUMERO;
				}
				break;
			case E_BOOL:
				if( c == '\n' || c == ' ' || c == '\t' ) {
					/* fin de booleano. */
					file.unget();
					estado = E_REG_NUMERO;
				} else {
					/* agrega caracteres al buffer. */
					tmpbuf += c;
				}
				break;
			case E_REG_CADENA:
				set_conf( identificador, ConfValue( tmpbuf ) );
				/* ignora el resto de la linea */
				if( c == '\n' ) estado = E_LEYENDO;
				else estado = E_COMENTARIO;
				break;
			case E_REG_NUMERO:
				{
				std::istringstream ss( tmpbuf );
				int i;

				ss >> i;
				set_conf( identificador, ConfValue( i ) );
				}
				/* ignora el resto de la linea */
				if( c == '\n' ) estado = E_LEYENDO;
				else estado = E_COMENTARIO;
				break;
			case E_REG_BOOL:
				if( tmpbuf == "true"  )
				set_conf( identificador, ConfValue( true ) );
				else if( tmpbuf == "false" )
				set_conf( identificador, ConfValue( false ) );
#if 0
				else /* TODO: error en valor booleano. */
#endif
				/* ignora el resto de la linea */
				if( c == '\n' ) estado = E_LEYENDO;
				else estado = E_COMENTARIO;
				break;
		}
	}
	#undef E_LEYENDO
	#undef E_COMENTARIO
	#undef E_IDENTIFICADOR
	#undef E_VALOR
	#undef E_CADENA	
	#undef E_NUMERO	
	#undef E_BOOL
	#undef E_REG_CADENA	
	#undef E_REG_NUMERO
	#undef E_REG_BOOL
}

