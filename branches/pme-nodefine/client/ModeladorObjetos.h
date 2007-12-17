#ifndef MODELADOROBJETOS_H_INCLUDED
#define MODELADOROBJETOS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

#include <math.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <SDL.h>
#include <assert.h>
#include "ObjetoVisual.h"
#include "ColeccionObjetos.h"
#include "PosicionGraf.h"
#include <iostream>
#include <string>
#include <math.h>
#include <map>
#include <list>

class ModeladorObjetos{
    ColeccionObjetos ColeccionOBJ;
    public:
        ModeladorObjetos();

        void hidratar();
    private:
        //metodo q dibuja el objeto q se le pasa por referencia
        //en el la posicion actual de la pantalla
        void DibujarObjeto(ObjTextura* objTex);

    public:
        //dibujar objeto em lugar determinado para la vista del observador
        void DibujarObjetoObservadorPosicion(Posicion_Graf* P,char Nombre);

        //dibujar objeto en posicion determinado
        void DibujarObjetoPosicion(Posicion_Graf* P,char Nombre);

};

#endif // MODELADOROBJETOS_H_INCLUDED
