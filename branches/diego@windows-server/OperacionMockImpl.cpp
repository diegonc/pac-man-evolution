#include "OperacionMockImpl.h"
#include "MundoMockImpl.h"
#include "Mapa.h"

void OperacionMockImpl::ejecutar()
{
	Mapa& mapa = MundoMockImpl::get_instance().get_mapa_activo();
	
	mapa.mover( 1, Mapa::Norte );
}
