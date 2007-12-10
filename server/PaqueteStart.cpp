#include "PaqueteStart.h"

namespace {
	const int ID = 1;
}

PaqueteStart::PaqueteStart() : Paquete( ID )
{
}

PaqueteStart::PaqueteStart(int id_cliente):Paquete( ID ){
	this->id_cliente = id_cliente;
}

void PaqueteStart::serialize( OutputBitStream& bs ){
	Paquete::serialize( bs );
	bs.skip();
	
	bs.append(16,id_cliente);
}

void PaqueteStart::deserialize( InputBitStream& bs ) {
	bs.skip(); // Campo auxiliar no utilizado.
	id_cliente = bs.read( 16 );
}

Operacion * PaqueteStart::get_operacion(){
	throw "PaqueteStart::get_operacion: Implementacion pendiente.";
}
