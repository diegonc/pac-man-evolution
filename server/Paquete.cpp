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
