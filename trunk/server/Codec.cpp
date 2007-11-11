#include "Codec.h"

S_ptr<Codec> Codec::instancia;

S_ptr<Codec> Codec::get_instancia(){
	if( instancia.es_nulo() )
		instancia = S_ptr<Codec>(new Codec());
	return instancia;	
}

Codec::Codec(){}
Codec::~Codec(){}
Codec::Codec(Codec& c){}
	
Operacion* procesar( Paquete* pkt ){
	return 0;	
}
Paquete* procesar( Operacion* op ){
	return 0;	
}
