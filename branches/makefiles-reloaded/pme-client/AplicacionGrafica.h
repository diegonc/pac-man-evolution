#ifndef APLICACIONGrafica_H_INCLUDED
#define APLICACIONGrafica_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

#include <math.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <SDL.h>
#include <assert.h>
#include "EstadoAplicacion.h"
#include "ObjetoVisual.h"
#include "PosicionGraf.h"
#include "Escenario.h"
#include "CargadordeTexturas.h"
#include "ModeladorObjetos.h"
#include "SelectorCamara.h"
#include "MiniMapa.h"
#include <iostream>
#include <string>
#include <math.h>
#include <map>
#include <list>

#include "../pme-server/KeyOp.h"

class AplicacionGrafica{
        //estadp de la aplicaccion
        EstadoAplicacion AppEstado;
	SelectorCamara Camara;
	SDL_Surface* Mapa;
	MiniMapa minimapa;
           
	private: 
		Escenario escenario;

        ModeladorObjetos ModeladorOBJ;
		
		bool CamaraPrimeraPersona;
    public:

        AplicacionGrafica(){
            CamaraPrimeraPersona=true;
        }
		
	void CambiarCamara();

        EstadoAplicacion* getEstadoAplicacion();

        ModeloServidor* getModelo();

        //inicializacion de OpenGL
        bool InitGL(SDL_Surface *S);

        //inicializacion de Datos necesarios para interfase grafica
        bool Initialize();

        //finalizar y liberar recursos
        void Deinitialize();

        // dibujo el modelo visual
        void Draw(SDL_Surface *Screen);
      
		

    private:
        //dibujo el modelo 3D
        void Draw3D(SDL_Surface *S);

        //get Angulo Desde Direccion
        int getAnguloDireccion(Direccion &dir);

        //dibuja en 2D
        void Draw2D(SDL_Surface *S);
   
};
#endif // APLICACION_H_INCLUDED
