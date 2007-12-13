#include "PaqueteInit.h"


PaqueteInit::PaqueteInit() : PaqueteInitCommon()
{

}	

Operacion* PaqueteInit::get_operacion(){
   return NULL;
}

PaqueteInit::PaqueteInit(bool pacman, S_ptr<MapaBajoNivel> m ):PaqueteInitCommon(pacman, m){}
