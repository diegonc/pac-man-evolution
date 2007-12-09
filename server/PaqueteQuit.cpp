#include "PaqueteQuit.h"

namespace {
	const char ID = 4;
}

PaqueteQuit::PaqueteQuit(): Paquete(ID)
{

}

void PaqueteQuit::deserialize( InputBitStream& bs )
{
    bs.skip();
}

void PaqueteQuit::serialize( OutputBitStream& bs )
{
    Paquete::serialize( bs ); // Escribe version de protocolo e ID de paquete.
    bs.grow(3);
	bs.skip();

}
