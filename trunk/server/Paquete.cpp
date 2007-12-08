#include "Paquete.h"

Paquete::Paquete()
{
}

Paquete::~Paquete()
{
}

Paquete::Paquete( char tipo ) : tipo( tipo )
{
}

char Paquete::get_tipo()
{
	return tipo;
}

Paquete* Paquete::crear( int tipo ){
      return 0;
}

void Paquete::serialize( OutputBitStream& bs )
{
	// Version
	bs.append( 2, 0 /* TODO: hardcoded?!*/	);
	// Tipo
	bs.append( 3, tipo );
}
