#ifndef CargadorDe3DS_H_INCLUDED
#define CargadorDe3DS_H_INCLUDED


#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "ObjetoVisual.h"

class CargadorDe3DS{
    public:
    static char Cargar3DS(ObjetoVisual* Objeto,const char *p_filename);
};
#endif
