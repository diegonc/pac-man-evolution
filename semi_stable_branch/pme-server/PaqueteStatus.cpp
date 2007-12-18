#include "PaqueteStatus.h"

#include "../common/OperacionNula.h"

PaqueteStatus::PaqueteStatus(std::list<NovedadComestible>* Novedad, S_ptr<ModeloCommon> modelo): PaqueteStatusCommon(Novedad,modelo){

}

PaqueteStatus::PaqueteStatus(): PaqueteStatusCommon()
{

}
PaqueteStatus::~PaqueteStatus(){}

Operacion * PaqueteStatus::get_operacion(){
   return new OperacionNula();
}
