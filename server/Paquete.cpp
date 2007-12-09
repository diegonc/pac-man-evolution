#include "Paquete.h"

#include "PaqueteTecla.h"
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
    //TODO: HACERLO BIEN ESTOOOOO!!!!!
	Paquete * p;
	switch(tipo){
		case 5:	
			p = new PaqueteTecla();
			break;
		default:
			p = 0;
	}
	return p;
}

void Paquete::serialize( OutputBitStream& bs )
{
	// Version
	bs.append( 2, 0 /* TODO: hardcoded?!*/	);
	// Tipo
	bs.append( 3, tipo );
}
