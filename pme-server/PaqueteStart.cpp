#include "PaqueteStart.h"

#include <server/OperacionNula.h>

PaqueteStart::PaqueteStart() : PaqueteStartCommon()
{
}

PaqueteStart::PaqueteStart(int id_cliente):PaqueteStartCommon( id_cliente ){

}

Operacion * PaqueteStart::get_operacion(){
      return new OperacionNula();
}
