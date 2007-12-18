#include "PaqueteStop.h"

#include "../common/OperacionNula.h"

PaqueteStop::PaqueteStop() : PaqueteStopCommon()
{

}	

Operacion* PaqueteStop::get_operacion(){
   return new OperacionNula();
}

