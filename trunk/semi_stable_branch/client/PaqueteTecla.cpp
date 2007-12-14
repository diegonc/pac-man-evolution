#include "PaqueteTecla.h"

#include "../common/OperacionNula.h"

PaqueteTecla::PaqueteTecla(unsigned int id_cliente,int Flecha) : PaqueteTeclaCommon( id_cliente, Flecha )
{
}

PaqueteTecla::PaqueteTecla(unsigned int id_cliente) : PaqueteTeclaCommon( id_cliente )
{
}

Operacion * PaqueteTecla::get_operacion(){
	return new OperacionNula();
}
