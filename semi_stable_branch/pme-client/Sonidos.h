#ifndef SONIDO_H_INCLUDED
#define SONIDO_H_INCLUDED

#include <SDL.h>
#include <SDL_mixer.h>
#include <iostream>

class Sonido{
	Mix_Music *musica;
	public:
	Sonido(std::string NombreArch);

	void Play(int vecesRep);

	void Parar();

	~Sonido();

};

#endif
