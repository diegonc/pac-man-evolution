#include "Direccion.h"

Direccion Direccion::Norte = Direccion( 0 );
Direccion Direccion::Sur = Direccion( 1 );
Direccion Direccion::Este = Direccion( 2 );
Direccion Direccion::Oeste = Direccion( 3 );

Direccion Direccion::combinar( int i )
{
	return Direccion( (dir + i) % 4 );
}
