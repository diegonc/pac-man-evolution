#include "PaqueteQuit.h"

#include <server/OperacionNula.h>

PaqueteQuit::PaqueteQuit() : PaqueteQuitCommon()
{

}	

Operacion* PaqueteQuit::get_operacion(){
   return new OperacionNula();
}

