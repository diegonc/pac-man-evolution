#include "PaqueteStop.h"

#include <server/OperacionNula.h>

PaqueteStop::PaqueteStop() : PaqueteStopCommon()
{

}	

Operacion* PaqueteStop::get_operacion(){
   return new OperacionNula();
}

