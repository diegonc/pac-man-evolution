#ifndef APLICACION_INCLUDED
#define APLICACION_INCLUDED

#include <stdio.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL.h>
#include "ObjetoVisual.h"
#include "EstadoAplicacion.h"
#include <stdio.h>
#include "AplicacionGrafica.h"
#include "../../server/PaqueteTecla.h"
#include "JugadorLocal.h"
#include "../../common/smart_pointer.h"
//#include "../../server/Cliente.h"
#include "../../server/EscritorCliente.h"


#define APP_NAME	"Pacman-Evolution"
#define APP_VERSION	"0.5"

// ResolucionAncho de pantalla
#define SCREEN_W	800// <<---ALAN CANSADO
// ResolucionAlto de pantalla
#define SCREEN_H	600
//profundidad de colores
#define SCREEN_BPP	32

class Aplicacion{
    //el programa se encuentra dibujando (para bucle de dibujo)
    bool BucleActivo;
    //superficie para el pintado;
    SDL_Surface *Screen;
    //OpenGL
    AplicacionGrafica APPG;

    Cliente* cliente;

    public:

    Aplicacion(Cliente* Cli){
        Screen = NULL;
        BucleActivo=true;
        this->cliente=Cli;
    }

    AplicacionGrafica* getAplicacionGrafica(){
        return &APPG;
    }

    SDL_Surface* getScreen(){
        return Screen;
    }

    bool isProgramLooping(){
        return BucleActivo;
    }

    void TerminarLoop(){
        BucleActivo=false;
    }


    //InicializacionTimers
    bool InitTimers(Uint32 *);
    //Crear Ventana
    bool CreateWindowGL( int, int, int, Uint32);
    //Cargar Icono de Ventana
    SDL_Surface *SetUpIcon(char *);

    // Resize
    void ReshapeGL(int, int);
    // Cambia el modo de visualizacion de la ventana
    void ToggleFullscreen();

    //actualiza el modelo visual segun los eventos de teclado recibidos
    void Update(Uint32 Milliseconds, Uint8 *Keys);
    // TerminarAplicacion
    void TerminateApplication();

};

//punto de entrada;
int main(int, char **);

#endif // APLICACION_INCLUDED
