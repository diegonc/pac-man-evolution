#include "PaqueteStart.h"

#include "OperacionStart.h"

PaqueteStart::PaqueteStart() : PaqueteStartCommon()
{
}

PaqueteStart::PaqueteStart(int id_cliente):PaqueteStartCommon( id_cliente ){

}

Operacion * PaqueteStart::get_operacion(){
   std::cout << "Va para el cliente " << id_cliente  <<"\n";
   return new OperacionStart( id_cliente );
}
