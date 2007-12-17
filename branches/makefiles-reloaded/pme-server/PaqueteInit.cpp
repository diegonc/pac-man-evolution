#include "PaqueteInit.h"

#include <server/OperacionNula.h>

PaqueteInit::PaqueteInit() : PaqueteInitCommon()
{

}	

Operacion* PaqueteInit::get_operacion(){
   return new OperacionNula();
}

PaqueteInit::PaqueteInit(bool pacman, S_ptr<MapaBajoNivel> m ):PaqueteInitCommon(pacman, m){}
