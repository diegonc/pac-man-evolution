#include "PaqueteTecla.h"

namespace {
	const char ID = 5;
}

PaqueteTecla::PaqueteTecla() : Paquete( ID )
{

}

KeyOp* PaqueteTecla::get_KeyOp(){
    return OperacionTecla;
}

void PaqueteTecla::set_KeyOp(KeyOp* OperTecla){
    OperacionTecla=OperTecla;
}


void PaqueteTecla::deserialize( InputBitStream& bs )
{
    /*
    bs.grow(8);
    int Flecha=bs.read(8);
    ?????
    */
    int Flecha=bs.read(3);
    bs.skip();


    OperacionTecla=new KeyOp(KeyOp::get_teclaFormatoOperacion(Flecha));

}

void PaqueteTecla::serialize( OutputBitStream& bs )
{
    if (!OperacionTecla){
        std::cerr << "No se seteo la operacion";
        return;
    }

	Paquete::serialize( bs ); // Escribe version de protocolo e ID de paquete.

	bs.append( 3, KeyOp::get_teclaFormatoPaquete(OperacionTecla));
}
