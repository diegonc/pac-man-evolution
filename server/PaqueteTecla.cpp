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

PaqueteTecla::PaqueteTecla(int id_cliente,int Flecha) : Paquete( ID )
{
	this->id_cliente = id_cliente;
	this->FlechaProt=al_protocolo(Flecha);
}

PaqueteTecla::PaqueteTecla(int id_cliente) : Paquete( ID )
{
	this->id_cliente = id_cliente;
}



void PaqueteTecla::deserialize( InputBitStream& bs )
{
    /*
    bs.grow(8);
    int Flecha=bs.read(8);
    ?????
    */
    FlechaProt=bs.read(3);
    bs.skip();
}

void PaqueteTecla::serialize( OutputBitStream& bs )
{
	Paquete::serialize( bs ); // Escribe version de protocolo e ID de paquete.

	bs.append( 3, FlechaProt );
}
Operacion * PaqueteTecla::get_operacion(){
	return new KeyOp( desde_protocolo(FlechaProt) , id_cliente );
}
