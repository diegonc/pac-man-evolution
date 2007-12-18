#ifndef _OPERACION_NULA_H
#define _OPERACION_NULA_H

#include "Operacion.h"

class OperacionNula : public Operacion {
   public:
      OperacionNula(){}

      ~OperacionNula(){}

      void ejecutar(ModeloCommon &modelo) {/*NO HAGO NADA; ES NULA*/}
   
};

#endif /*_OPERACION_NULA_H*/
