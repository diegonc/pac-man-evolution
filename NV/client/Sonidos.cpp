#include "Sonidos.h"


Sonido::Sonido(std::string NombreArch){
	musica = Mix_LoadMUS ( NombreArch.c_str() );
}

void Sonido::Play(int vecesRep){
	Mix_PlayMusic ( musica, vecesRep ); // Reproducimos infinitas veces el archivo cargado en la variable música.
}

void Sonido::Parar(){
	Mix_HaltMusic ( );         // Paramos la música. No tenemos que pasarle parámetros.
	
}

// Luego liberamos la variable sonido:
Sonido::~Sonido(){
	Parar();
	Mix_FreeMusic ( musica );
}

