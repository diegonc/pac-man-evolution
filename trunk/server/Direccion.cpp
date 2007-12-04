#include "Direccion.h"

const int Direccion::Norte = _NORTE;
const int Direccion::Sur = _SUR;
const int Direccion::Este = _ESTE;
const int Direccion::Oeste = _OESTE;

Direccion::Direccion( int i )
{
	dir = i;
}
Direccion::Direccion(){
	dir = Direccion::Norte;
}
void Direccion::combinar( int i )
{
	this->dir = ( (dir + i) % 4 );
}
const int Direccion::get_dir(){
	return this->dir;
}
