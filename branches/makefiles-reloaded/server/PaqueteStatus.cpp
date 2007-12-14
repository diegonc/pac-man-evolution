#include "PaqueteStatus.h"

#include "../common/OperacionNula.h"

PaqueteStatus::PaqueteStatus(): PaqueteStatusCommon()
{

}
PaqueteStatus::~PaqueteStatus(){}

Operacion * PaqueteStatus::get_operacion(){
   return new OperacionNula();
}
