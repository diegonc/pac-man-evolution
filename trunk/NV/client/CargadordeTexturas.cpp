#include "CargadordeTexturas.h"

//codigo q carga una textura del path espesificado de un archivo BMP
void CargadorDeTexturas::CargarTextura(GLuint* texture,std::string nombrearchBMP){
    //superficie SDL
    SDL_Surface *surface;
    surface = SDL_LoadBMP(nombrearchBMP.c_str());

    //la imagen no tiene un ancho de potencia de 2
    if ( (surface->w & (surface->w - 1)) != 0 ) {
        printf("la imagen no tiene un ancho de potencia de 2\n");
    }

    //la imagen no tiene un alto de potencia de 2
    if ( (surface->h & (surface->h - 1)) != 0 ) {
        printf("la imagen no tiene un alto de potencia de 2\n");
    }

    //le aviso a openGL q agregue una textura nueva
    glGenTextures( 1, texture );
    //selecciono la textura recien agregada
    glBindTexture (GL_TEXTURE_2D, *texture);

    //seteo parametros de la textura
    //los primeros 2 sirven para q se visualize mejor la misma
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    //estos 2 sirven para q cuando se necesite q la textura mas de una vez q se repita
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    //termino de configurar la textura q le pase a OPENGL
    glTexImage2D( GL_TEXTURE_2D, 0, 3, surface->w, surface->h, 0,
                  GL_BGR, GL_UNSIGNED_BYTE, surface->pixels );

    //libero la memoria de la superfice SDL utilizada de forma temporal
    if ( surface ) {
        SDL_FreeSurface( surface );
    }

    //selecciono ninguna textura para los sig modelados;
    glBindTexture (GL_TEXTURE_2D, 0);
}



