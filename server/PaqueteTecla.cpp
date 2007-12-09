#include "PaqueteTecla.h"

namespace {
	const char ID = 5;

	int flecha_map[4] = { 
				KeyOp::arriba,    /* arriba ( formato red: 0 ) */
			    KeyOp::abajo,     /* abajo ( formato red: 1 ) */
			    KeyOp::izquierda, /* izquierda ( formato red: 2 ) */
			    KeyOp::derecha    /* derecha ( formato red: 3 ) */
	};

	int al_protocolo( int flecha )
	{
		for( int i=0; i<4; i++ )
			if( flecha == flecha_map[i] )
				return i;

		/* No esta! y ahora ??! */
		return -1;
	}

	int desde_protocolo( int flecha )
	{
		if( (flecha >=0) && (flecha<4) )
			return flecha_map[flecha];

		/* No esta! y ahora ??! */
		return -1;
	}
}

PaqueteTecla::PaqueteTecla() : Paquete( ID )
{

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


    OperacionTecla=new KeyOp( desde_protocolo(Flecha) );

}

void PaqueteTecla::serialize( OutputBitStream& bs )
{
    if (!OperacionTecla){
        std::cerr << "No se seteo la operacion";
        return;
    }

	Paquete::serialize( bs ); // Escribe version de protocolo e ID de paquete.

	bs.append( 3, al_protocolo( OperacionTecla->get_flecha() ) );
}
Operacion * PaqueteTecla::get_operacion(){
	return OperacionTecla;
}
