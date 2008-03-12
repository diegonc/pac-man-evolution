#include "PaqueteStop.h"

#include "OperacionStop.h"

PaqueteStop::PaqueteStop() : PaqueteStopCommon()
{

}	

Operacion* PaqueteStop::get_operacion(){
   return new OperacionStop(razon,puntuacion);
}

