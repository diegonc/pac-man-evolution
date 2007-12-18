#include <common/ConfValue.h>
#include <cassert>

ConfValue::ConfValue( unsigned int valor )
{
	tipo = ConfValue::CV_NUMERO;
	numero = valor;
}

ConfValue::ConfValue( std::string valor )
{
	tipo = ConfValue::CV_TEXTO;
	cadena = new std::string( valor );
}

ConfValue::ConfValue( const char* valor )
{
	tipo = ConfValue::CV_TEXTO;
	cadena = new std::string( valor );
}

ConfValue::ConfValue( bool valor )
{
	tipo = ConfValue::CV_BOOL;
	booleano = valor;
}

ConfValue::ConfValue( const ConfValue& cv )
{
	tipo = cv.tipo;
	switch( tipo ) {
		case CV_TEXTO:
			cadena = new std::string( *(cv.cadena) );
			break;	
		case CV_BOOL:
		case CV_NUMERO:
			numero = cv.numero;
		case CV_NULO:
			break;
	}
}

ConfValue::~ConfValue()
{
	
	if( tipo == ConfValue::CV_TEXTO ) {
		delete cadena;
	}
}

ConfValue& ConfValue::operator=( const ConfValue& c )
{
	if( &c != this ) {
		tipo = c.tipo;

		if( tipo == ConfValue::CV_TEXTO ) {
			if( cadena )
				delete cadena;
			cadena = new std::string( *(c.cadena) );
		}
		else 
			numero = c.numero;
	}
	return *this;
}

unsigned int ConfValue::get_numero() const
{
	assert( tipo == ConfValue::CV_NUMERO );
	return numero;
}

std::string ConfValue::get_texto() const
{
	assert( tipo == ConfValue::CV_TEXTO );
	return *cadena;
}

bool ConfValue::get_booleano() const
{
	assert( tipo == ConfValue::CV_BOOL );
	return booleano;
}

bool ConfValue::operator==( const ConfValue& otro ) const
{
	if( tipo == otro.tipo ) {
		switch( tipo ) {
			case ConfValue::CV_TEXTO:
				return *cadena == *otro.cadena;
			case ConfValue::CV_NUMERO:
				return numero == otro.numero;
			case ConfValue::CV_BOOL:
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
		case ConfValue::CV_TEXTO:
			out << "TIPO: TEXTO V: " << *cadena;
			break;
		case ConfValue::CV_NUMERO:
			out << "TIPO: NUMERO V: " << numero;
			break;
		case ConfValue::CV_BOOL:
			out << "TIPO: BOOL V: " << booleano;
			break;
		case ConfValue::CV_NULO:
			out << "TIPO: NULO";
			break;
	}
}
