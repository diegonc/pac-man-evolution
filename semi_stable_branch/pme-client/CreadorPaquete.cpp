#include <server/Paquete.h>

#include "PaqueteInit.h"
#include "PaqueteStart.h"
#include "PaqueteStatus.h"
#include "PaqueteStop.h"
#include "PaqueteQuit.h"
#include "PaqueteTecla.h"
#include "PaqueteMensaje.h"


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
