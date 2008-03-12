#include <server/Paquete.h>
/*
#ifndef PROGRAMA_CLIENTE
   #include "../server/PaqueteInit.h"
   #include "../server/PaqueteStart.h"
   #include "../server/PaqueteStatus.h"
   //#include "../server/PaqueteStop.h"
   #include "PaqueteQuit.h"
   #include "../server/PaqueteTecla.h"
   #include "PaqueteMensaje.h"
#else

   #include "../client/PaqueteInit.h"
   #include "../client/PaqueteStart.h"
   #include "../client/PaqueteStatus.h"
   //#include "../client/PaqueteStop.h"
   #include "PaqueteQuit.h"
   #include "../client/PaqueteTecla.h"
   #include "PaqueteMensaje.h"   
#endif

*/
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

#if 0
Este metodo se deja para ser definido en modulos de los programas
cliente y servidor.
Asi, los include en el comienzo de este archivo no son necesarios,
y se puede eliminar la compilacion condicional.

Paquete* Paquete::crear( int tipo ,unsigned int id_cliente ){

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
		case 3:
			p = new PaqueteStop();
			break;
		case 4:
			p = new PaqueteQuit();
			break;
		case 5:	
			p = new PaqueteTecla(id_cliente);
			break;
		case 6:
			p = new PaqueteMensaje();
			break;
		default:
			p = NULL;
	}
	return p;
}
#endif

void Paquete::serialize( OutputBitStream& bs )
{
	// Version
	bs.append( 2, 0 /* TODO: hardcoded?!*/	);
	// Tipo
	bs.append( 3, tipo );
}
