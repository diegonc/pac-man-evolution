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

ConfValue::ConfValue( const ConfValue& cv )
{
	tipo = cv.tipo;
	switch( tipo ) {
		case TEXTO:
			cadena = new std::string( *(cv.cadena) );
			break;	
		case BOOL:
		case NUMERO:
			numero = cv.numero;
			break;
	}
}

ConfValue::~ConfValue()
{
	
	if( tipo == ConfValue::TEXTO ) {
		assert( cadena != 0 );
		//delete cadena;
		std::cerr << "Borra puntero: " << std::hex << (int)cadena;
		std::cerr << " de Configuracion: " << std::hex;
		std::cerr << (int) this;
		std::cerr << std::endl;
	}
}

ConfValue& ConfValue::operator=( const ConfValue& c )
{
	if( &c != this ) {
		tipo = c.tipo;

		if( tipo == ConfValue::TEXTO )
			cadena = new std::string( *(c.cadena) );
		else 
			numero = c.numero;
	}
	return *this;
}

int ConfValue::get_numero() const
{
	assert( tipo == ConfValue::NUMERO );
	return numero;
}

std::string ConfValue::get_texto() const
{
	assert( tipo == ConfValue::TEXTO );
	return *cadena;
}

bool ConfValue::get_booleano() const
{
	assert( tipo == ConfValue::BOOL );
	return booleano;
}

bool ConfValue::operator==( const ConfValue& otro ) const
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

void ConfValue::dump( std::ostream& out ) const
{
	switch( tipo ) {
		case ConfValue::TEXTO:
			out << "TIPO: TEXTO V: " << *cadena;
			break;
		case ConfValue::NUMERO:
			out << "TIPO: NUMERO V: " << numero;
			break;
		case ConfValue::BOOL:
			out << "TIPO: BOOL V: " << booleano;
			break;
	}
}
