#include "PaqueteStart.h"

PaqueteStart::PaqueteStart(int id_cliente):Paquete(1){
	this->id_cliente = id_cliente;
}
void PaqueteStart::serialize( OutputBitStream& bs ){
	Paquete::serialize( bs );
	
	bs.append(16,id_cliente);
}
void PaqueteStart::deserialize( InputBitStream& bs ){

}
Operacion * PaqueteStart::get_operacion(){
	return 0;
}
