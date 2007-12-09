#include "PaqueteStart.h"

PaqueteStart::PaqueteStart(int id_cliente):Paquete(1){
	
}
void PaqueteStart::serialize( OutputBitStream& bs ){
	
}
void PaqueteStart::deserialize( InputBitStream& bs ){

}
Operacion * PaqueteStart::get_operacion(){
	return 0;
}
