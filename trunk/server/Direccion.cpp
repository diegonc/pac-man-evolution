#include "Direccion.h"

/*
Direccion Direccion::Norte = Direccion( 0 );
Direccion Direccion::Sur = Direccion( 1 );
Direccion Direccion::Este = Direccion( 2 );
Direccion Direccion::Oeste = Direccion( 3 );
*/
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
	
/*Direccion::Direccion(Direccion &d){
	this->dir = d.dir;
}*/
