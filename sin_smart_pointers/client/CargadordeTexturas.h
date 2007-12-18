#ifndef CARGADORDETEXTURAS_H_INCLUDED
#define CARGADORDETEXTURAS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>


#include <math.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <SDL.h>
#include <assert.h>

#include <iostream>
#include <string>
#include <math.h>
#include <map>
#include <list>

class CargadorDeTexturas{
        public:
        //codigo q carga una textura del path espesificado de un archivo BMP
        static void CargarTextura(GLuint* texture,std::string nombrearchBMP);


};

#endif // CARGADORDETEXTURAS_H_INCLUDED
