#ifndef SONIDO_H_INCLUDED
#define SONIDO_H_INCLUDED

#include <SDL.h>
#include <SDL_mixer.h>
#include <iostream>

class Sonido{
	Mix_Music *musica;
	public:
	Sonido(std::string NombreArch);

	//A continuación cargamos el sonido en dicha varible con la siguiente función:


	/*
	Una vez que hemos cargado el sonido, pasamos a reproducirlo. Tenemos que pasarle 3 parametros:
	- El canal que le vamos a asignar.
	- El nombre de la varible donde lo hemos cargado.
	- El número de veces que queremos que se repita ( 1--> una vez, 2--> dos veces, etc. Si le pasamos -1 se repetira indefinidamente ).
	*/
	void Play(int vecesRep);

	//Ahora si este sonido, una vez reproducido, no nos sirve para nada más lo eliminamos de la siguiente forma:
	//Primero lo paramos ( para asegurarnos ) pasandole como parámetro el canal que anteriormente le habiamos asignado.
	void Parar();

	// Luego liberamos la variable sonido:
	~Sonido();

};

#endif
