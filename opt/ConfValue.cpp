#include "ConfValue.h"
#include <cassert>

ConfValue::ConfValue( int valor )
{
	tipo = Tipo::NUMERO;
	valor.numero = valor;
}

ConfValue::ConfValue( char* valor )
{
	tipo = Tipo::TEXTO;
	valor.cadena = valor;
}

ConfValue::ConfValue( bool valor )
{
	tipo = Tipo::BOOL;
	valor.boleano = valor;
}

int ConfValue::get_numero()
{
	assert( tipo == Tipo::NUMERO );
	return valor.numero;
}

char* ConfValue::get_texto()
{
	assert( tipo == Tipo::TEXTO );
	return valor.cadena;
}

bool ConfValue::get_booleano()
{
	assert( tipo == Tipo::BOOL );
	return valor.booleano;
}
