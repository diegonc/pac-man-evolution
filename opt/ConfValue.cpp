#include "ConfValue.h"
#include <cassert>

ConfValue::ConfValue( int valor )
{
	tipo = ConfValue::NUMERO;
	numero = valor;
}

ConfValue::ConfValue( std::string valor )
{
	tipo = ConfValue::TEXTO;
	cadena = new std::string( valor );
}

ConfValue::ConfValue( bool valor )
{
	tipo = ConfValue::BOOL;
	booleano = valor;
}

ConfValue::~ConfValue()
{
	if( tipo == ConfValue::TEXTO )
		delete cadena;
}

int ConfValue::get_numero()
{
	assert( tipo == ConfValue::NUMERO );
	return numero;
}

std::string ConfValue::get_texto()
{
	assert( tipo == ConfValue::TEXTO );
	return *cadena;
}

bool ConfValue::get_booleano()
{
	assert( tipo == ConfValue::BOOL );
	return booleano;
}

bool ConfValue::operator==( const ConfValue& otro )
{
	if( tipo == otro.tipo ) {
		switch( tipo ) {
			case ConfValue::TEXTO:
				return *cadena == *otro.cadena;
			case ConfValue::NUMERO:
				return numero == otro.numero;
			case ConfValue::BOOL:
				return booleano == otro.booleano;
			default:
				return true;
		}
	}
	return false;
}
