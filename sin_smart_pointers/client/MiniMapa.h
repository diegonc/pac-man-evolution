#ifndef MINIMAPA_H
#define MINIMAPA_H



#include <SDL.h>
#include "JugadorLocal.h"
#include "ModeloServidor.h"
#include <math.h>


class MiniMapa{
	//Mapa: 294 x 294
	SDL_Surface* Mapa;
	//Casillero: 32 x 32
	SDL_Surface* Casillero;	
	//Objetos: 24 x 24
	SDL_Surface* Pacman;
	SDL_Surface* Fantasma;
	SDL_Surface* PowerUP;
	SDL_Surface* Frutita;
	SDL_Surface* Quesito;

	const static int Marco=3;
	const static int DimCasillero=32;
	const static int DimObjeto=24;
	const static int DimMiniMapa=294;
	const static int ScreenResolutionX=800;
	const static int InitXMiniMapa=ScreenResolutionX-DimMiniMapa;
	const static int InitYMiniMapa=0;
	const static int DimensionTablero=9;

	public:

	MiniMapa();

	~MiniMapa();

	void ejecutar(SDL_Surface* Screen);


	private:

	void DibujarJugador(SDL_Surface* Screen, Jugador* jug, int ImgXCurr, int ImgYCurr);

	void DibujarComestible(SDL_Surface* Screen, Comestible * Comest, int ImgXCurr, int ImgYCurr);

	void DibujarCasillero(SDL_Surface* Screen,int ImgXCurr,int ImgYCurr);

	void DibujarObjeto(SDL_Surface* Screen, SDL_Surface* TextObj, int ImgXCurr, int ImgYCurr);

	void Dibujar(Jugador* jug, SDL_Surface* Screen);

	bool hayEstructural(Posicion& P);

	public:

	void CargarTexturas();

	private:

	void CargarSDLSurface(SDL_Surface** Textura,char* Nombre);


};

#endif
