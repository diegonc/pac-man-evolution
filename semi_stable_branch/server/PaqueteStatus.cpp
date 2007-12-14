#include "PaqueteStatus.h"

#include "../common/OperacionNula.h"

PaqueteStatus::PaqueteStatus(std::list<NovedadComestible>* Novedad): PaqueteStatusCommon(Novedad){

}

PaqueteStatus::PaqueteStatus(): PaqueteStatusCommon()
{

}
PaqueteStatus::~PaqueteStatus(){}

Operacion * PaqueteStatus::get_operacion(){
   return new OperacionNula();
}
