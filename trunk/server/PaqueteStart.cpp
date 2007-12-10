#include "PaqueteStart.h"

PaqueteStart::PaqueteStart(int id_cliente):Paquete(1){
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
