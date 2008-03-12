#include "NotificadorMensajes.h"

NotificadorMensajes::NotificadorMensajes(): VisorMensajeCrit1(true,0),
			VisorMensajeCrit2(true,1),
			VisorMensaje1(true,3),
			VisorMensaje2(true,4),
			VisorMensaje3(true,5){
	VisorMensajeCrit1.CargarTextura();
	VisorMensajeCrit2.CargarTextura();
	VisorMensaje1.CargarTextura();
	VisorMensaje2.CargarTextura();
	VisorMensaje3.CargarTextura();
	BufferMensajes::get_instancia()->set_max_mensajes(3);		
	BufferMensajes::get_instancia()->set_max_mensajes_criticos(2);
}

void NotificadorMensajes::Ejecutar(SDL_Surface* Screen){
	std::queue<std::string> ColaMensajesCriticos=BufferMensajes::get_instancia()->get_mensajes_criticos();
	std::queue<std::string> ColaMensajes=BufferMensajes::get_instancia()->get_mensajes();
	std::string StringVacio="";

	if (!ColaMensajesCriticos.empty()){
		VisorMensajeCrit1.ImprimirFrase(Screen,ColaMensajesCriticos.front());
		ColaMensajesCriticos.pop();
		if (!ColaMensajesCriticos.empty()){
			VisorMensajeCrit2.ImprimirFrase(Screen,ColaMensajesCriticos.front());
		}else{
			VisorMensajeCrit2.ImprimirFrase(Screen,StringVacio);
		}
	}else{
		VisorMensajeCrit1.ImprimirFrase(Screen,StringVacio);
		VisorMensajeCrit2.ImprimirFrase(Screen,StringVacio);
	}

	if (!ColaMensajes.empty()){
		VisorMensaje1.ImprimirFrase(Screen,ColaMensajes.front());
		ColaMensajes.pop();
		if (!ColaMensajes.empty()){
			VisorMensaje2.ImprimirFrase(Screen,ColaMensajes.front());
			ColaMensajes.pop();
			if (!ColaMensajes.empty()){
				VisorMensaje3.ImprimirFrase(Screen,ColaMensajes.front());
			}else{
				VisorMensaje3.ImprimirFrase(Screen,StringVacio);	
			}
		}else{
			VisorMensaje3.ImprimirFrase(Screen,StringVacio);
			VisorMensaje2.ImprimirFrase(Screen,StringVacio);
		}
	}else{
		VisorMensaje3.ImprimirFrase(Screen,StringVacio);
		VisorMensaje2.ImprimirFrase(Screen,StringVacio);
		VisorMensaje1.ImprimirFrase(Screen,StringVacio);
	}
}

