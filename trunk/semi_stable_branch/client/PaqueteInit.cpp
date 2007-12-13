#include "PaqueteInit.h"

#include "OperacionInit.h"

PaqueteInit::PaqueteInit() : PaqueteInitCommon()
{

}	

Operacion* PaqueteInit::get_operacion(){
   return new OperacionInit( mapa, esPacman );
}

PaqueteInit::PaqueteInit(bool pacman, S_ptr<MapaBajoNivel> m ):PaqueteInitCommon(pacman, m){}
