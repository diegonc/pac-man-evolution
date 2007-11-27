#include "Direccion.h"

Direccion Direccion::Norte = Direccion( 0 );
Direccion Direccion::Sur = Direccion( 1 );
Direccion Direccion::Este = Direccion( 2 );
Direccion Direccion::Oeste = Direccion( 3 );

Direccion::Direccion( int i )
{
	dir = i;
}

Direccion Direccion::combinar( int i )
{
	return Direccion( (dir + i) % 4 );
}
/*Direccion::Direccion(Direccion &d){
	this->dir = d.dir;
}*/