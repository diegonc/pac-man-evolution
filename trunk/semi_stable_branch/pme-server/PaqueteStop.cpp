#include "PaqueteStop.h"

#include <server/OperacionNula.h>

PaqueteStop::PaqueteStop() : PaqueteStopCommon()
{

}	

PaqueteStop::PaqueteStop( char Razon, int Puntuacion) : PaqueteStopCommon(Razon, Puntuacion)
{

}	


Operacion* PaqueteStop::get_operacion(){
   return new OperacionNula();
}

