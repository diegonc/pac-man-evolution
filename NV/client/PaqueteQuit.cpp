#include "PaqueteQuit.h"

#include "../common/OperacionNula.h"

PaqueteQuit::PaqueteQuit() : PaqueteQuitCommon()
{

}	

Operacion* PaqueteQuit::get_operacion(){
   return new OperacionNula();
}

