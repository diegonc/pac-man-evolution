#include "PaqueteTecla.h"

#include "KeyOp.h"

PaqueteTecla::PaqueteTecla(int id_cliente,int Flecha) : PaqueteTeclaCommon(id_cliente, Flecha)
{
}

PaqueteTecla::PaqueteTecla(int id_cliente) : PaqueteTeclaCommon(id_cliente )
{	
}
Operacion * PaqueteTecla::get_operacion(){
	return new KeyOp( desde_protocolo(FlechaProt) , id_cliente );
}
