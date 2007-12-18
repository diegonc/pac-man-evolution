#ifndef ABECEDARIO_H
#define ABECEDARIO_H



#include <SDL.h>
#include "JugadorLocal.h"
#include "ModeloServidor.h"
#include <math.h>


class Abecedario{
	//Mapa: 256 x 256
	SDL_Surface* TextABC;
	//Mapa: 16 x 16
	SDL_Surface* TextLetra;

	const static int DimAbecedario=256;
	const static int DimLetra=16;
	const static int LetrasXFC= (int) (DimAbecedario/DimLetra);
	const static int ScreenWidth=800;
	const static int ScreenHeight=600;
	bool arriba;

	public:

	Abecedario(bool Arriba);

	~Abecedario();

	void ImprimirFrase(SDL_Surface* Screen,std::string Frase);


	private:

	void get_letra(char letra);

	void DibujarLetra(SDL_Surface* Screen, int ImgXCurr, int ImgYCurr);

	public:

	void CargarTextura();

	private:

	void CargarSDLSurface(SDL_Surface** Textura,char* Nombre);


};

#endif
