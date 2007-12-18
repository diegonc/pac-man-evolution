#include <server/PaqueteQuitCommon.h>

namespace {
	const char ID = 4;
}

PaqueteQuitCommon::PaqueteQuitCommon(): Paquete(ID)
{

}

void PaqueteQuitCommon::deserialize( InputBitStream& bs )
{
    bs.skip();
}

void PaqueteQuitCommon::serialize( OutputBitStream& bs )
{
    Paquete::serialize( bs ); // Escribe version de protocolo e ID de paquete.
    bs.skip();
}

