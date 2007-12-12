#include "ConfValue.h"
#include <cassert>

ConfValue::ConfValue( int valor )
{
	tipo = ConfValue::NUMERO;
	numero = valor;
}

ConfValue::ConfValue( char* valor )
{
	tipo = ConfValue::TEXTO;
	cadena = valor;
}

ConfValue::ConfValue( bool valor )
{
	tipo = ConfValue::BOOL;
	booleano = valor;
}

int ConfValue::get_numero()
{
	assert( tipo == ConfValue::NUMERO );
	return numero;
}

char* ConfValue::get_texto()
{
	assert( tipo == ConfValue::TEXTO );
	return cadena;
}

bool ConfValue::get_booleano()
{
	assert( tipo == ConfValue::BOOL );
	return booleano;
}
