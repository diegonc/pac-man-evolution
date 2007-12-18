#ifndef NOTIFICADOR_MENSAJES_H
#define NOTIFICADOR_MENSAJES_H

#include "Abecedario.h"
#include "BufferMensajes.h"
#include <SDL.h>

class NotificadorMensajes{
	Abecedario VisorMensajeCrit1;
	Abecedario VisorMensajeCrit2;
	Abecedario VisorMensaje1;
	Abecedario VisorMensaje2;
	Abecedario VisorMensaje3;
	public:

	NotificadorMensajes();

	void Ejecutar(SDL_Surface* Screen);
};

#endif
