#ifndef ESCENARIO_H_INCLUDED
#define ESCENARIO_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>


#include <math.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <SDL.h>
#include <assert.h>
#include "CargadordeTexturas.h"

#include <iostream>
#include <string>
#include "../../server/ModeloServidor.h"

class Escenario{
        GLuint ListaEscenario;
        ModeloServidor* Modelo;
        GLuint texturaPared;
        GLuint texturaPiso;

        public:

        void ModelarEscenario();

        void setModelo(ModeloServidor* Mod);

        Escenario();

        void Procesar();

        private:

        //agregar Pared desde las coordenadas especificadas
        void addPared(float xIn,float xFin,float yIn,float yFin);

        //agrega el piso en un rectangulo, con su textura correspondiente
        void addPiso(double xIn,double xFin,double yIn,double yFin);
      
        void DrawEscenario();






};


#endif // ESCENARIO_H_INCLUDED
