#include "Direccion.h"

/*
Direccion Direccion::Norte = Direccion( 0 );
Direccion Direccion::Sur = Direccion( 1 );
Direccion Direccion::Este = Direccion( 2 );
Direccion Direccion::Oeste = Direccion( 3 );
*/
const int Direccion::Norte = NORTE;
const int Direccion::Sur = SUR;
const int Direccion::Este = ESTE;
const int Direccion::Oeste = OESTE;

Direccion::Direccion( int i )
{
	dir = i;
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
