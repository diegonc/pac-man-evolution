#ifndef COLECCIONOBJETOS_H_INCLUDED
#define COLECCIONOBJETOS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

#include <math.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <SDL.h>
#include <assert.h>
#include "ObjetoVisual.h"
#include "CargadordeTexturas.h"
#include "Cargadorde3DS.h"
#include <iostream>
#include <string>
#include <math.h>
#include <map>
#include <list>
#include "../../server/ModeloServidor.h"


class ColeccionObjetos{
        //Objetos
        std::map<char,ObjTextura*> Objetos;

        public:
        ColeccionObjetos();

        void hidratar();

        ObjTextura* operator [] (char c)
        {
           return Objetos[c];
        }

        private:
        //carga los objetos q van a ser usados
        void CargarObjetos();

};
#endif // COLECCIONOBJETOS_H_INCLUDED
