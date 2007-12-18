#include "PaqueteInit.h"

#include "../common/OperacionNula.h"

PaqueteInit::PaqueteInit() : PaqueteInitCommon()
{

}	

Operacion* PaqueteInit::get_operacion(){
   return new OperacionNula();
}

PaqueteInit::PaqueteInit(bool pacman, MapaBajoNivel* m ):PaqueteInitCommon(pacman, m){}
