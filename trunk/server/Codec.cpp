#include "Codec.h"

Codec::Codec(){}
Codec::~Codec(){}
Codec::Codec(Codec& c){}
	
Operacion* Codec::procesar( Paquete* pkt ){
	return 0;	
}
Paquete* Codec::procesar( Operacion* op ){
	return 0;	
}
