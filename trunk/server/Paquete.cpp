#include "Paquete.h"
#include "PaqueteInit.h"
#include "PaqueteStart.h"
#include "PaqueteStatus.h"
//#include "PaqueteStop.h"
#include "PaqueteQuit.h"
#include "PaqueteTecla.h"
#include "PaqueteMensaje.h"

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
		case 0:
			p = new PaqueteInit();
			break;
		case 1:
			p = new PaqueteStart();
			break;
		case 2:
			p = new PaqueteStatus();
			break;
/*		case 3:
			p = new PaqueteStop();
			break;*/
		case 4:
			p = new PaqueteQuit();
		case 5:	
			p = new PaqueteTecla();
			break;
		case 6:
			p = new PaqueteMensaje();
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
