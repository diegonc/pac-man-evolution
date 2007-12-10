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
#include "../../common/observador.h"

class Escenario : public Observador{
        GLuint ListaEscenario;
        GLuint texturaPared;
        GLuint texturaPiso;
		bool Cargado;
		bool proceso;

        public:

        void ModelarEscenario();

        Escenario();

        void Procesar();
		
		bool loaded();

        private:

        //agregar Pared desde las coordenadas especificadas
        void addPared(float xIn,float xFin,float yIn,float yFin);

        //agrega el piso en un rectangulo, con su textura correspondiente
        void addPiso(double xIn,double xFin,double yIn,double yFin);
      
        void DrawEscenario();

		void actualizar(Observable * observable, void * param);




};


#endif // ESCENARIO_H_INCLUDED
