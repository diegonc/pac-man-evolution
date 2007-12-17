#include "Aplicacion.h"

////////////////////////////////////////
#include "../common/client_socket.h"
#include "../common/Cliente.h"
#include <stdexcept>
#include <string>
#include <iostream>
///////////////////////////////////////

//principal
int main(int argc, char **argv)
{

	//socket
	Socket_Cliente * socket = new Socket_Cliente(); //<<----Ponele que vaya aca

	try{

		//////////POR AHORA HARDCODED////////////////////
		std::string ip("201.231.232.12");
		unsigned int short puerto = 7777;
		socket->conectar(ip, puerto);
		Cliente cliente_del_modelo(1, socket); //WHAT ?????
		cliente_del_modelo.start();
		/////////////////////////////////////////////////
		Aplicacion APP(&cliente_del_modelo);
		//evento
		SDL_Event	E;
		//estado del teclado
		Uint8		*Keys;
		//flags de video
		Uint32		Vflags;
		//Tiempos Utilizados para el refresco
		//para tener en cuenta el tiempo de cada loop
		Uint32		TickCount;
		Uint32		LastCount;

		//Inicializo los Punteros
		//Screen = NULL;
		Keys = NULL;
		//inicializo el video para OPENGL(3D) y SDLSurface(2D)
		Vflags = SDL_HWSURFACE|SDL_OPENGLBLIT;

		//inicializo SDL
		SDL_Init(SDL_INIT_VIDEO);

		//le indico q cuando termine Envie un SDL_Quit
		atexit(SDL_Quit);

		//seteo inicialmente en fullscreen
		//Vflags|=SDL_FULLSCREEN;

		//seteo icono de aplicacion
		APP.SetUpIcon("Icon.bmp");

		//creo ventana con los defines de tamanio y los flags de Video
		APP.CreateWindowGL(SCREEN_W, SCREEN_H, SCREEN_BPP, Vflags);

		//Seteo Caption de ventana
		SDL_WM_SetCaption(APP_NAME, NULL);

		//obtengo el tiempoAntes del loop
		APP.InitTimers(&LastCount);

		//ejecuto la inicializacion de OPGL
		APP.getAplicacionGrafica()->InitGL(APP.getScreen());

		//ejecuto la inicializacion de la aplicacion
		APP.getAplicacionGrafica()->Initialize();

		//levanto el boolean del loop de dibujo
		//isProgramLooping = true;

		//mientras este levantado el flag
		while(APP.isProgramLooping())
		{
						//std::cout << " evento1"<< E.type <<  std::endl;
			//trato de chachear algun evento si es q se produjo


//trato de chachear algun evento si es q se produjo
			if(SDL_PollEvent(&E))
			{

//						std::cout << " evento"<< E.type <<  std::endl;
				//dependiendo del tipo
				switch(E.type)
				{
					//se cacheo el evento salir;
					case SDL_QUIT:
						{
							//bajo el flag de dibujado
							APP.TerminarLoop();
							break;
						}

					//hubo un resize
					case SDL_VIDEORESIZE:
						{
							//acomodo la pantalla de OpenGL
							APP.ReshapeGL(E.resize.w, E.resize.h);
							break;
						}

					//evento de actividad
					case SDL_ACTIVEEVENT:
						{
							//si cambio el estado y hay cambio de ventana
							if(E.active.state & SDL_APPACTIVE)
							{
								//si gano foco
								if(E.active.gain)
								{
									//ventana Visible
									APP.getAplicacionGrafica()->getEstadoAplicacion()->Visible = true;
								}
								else
								{
									//ventana Invisible
									APP.getAplicacionGrafica()->getEstadoAplicacion()->Visible = false;
								}
							}

							//si cambio el estado y es del mouse
							if(E.active.state & SDL_APPMOUSEFOCUS)
							{
								//si gano foco del mouse
								if(E.active.gain)
								{
									//levanto el flag
									APP.getAplicacionGrafica()->getEstadoAplicacion()->MouseFocus = true;
								}
								else
								{
									//lo bajo
									APP.getAplicacionGrafica()->getEstadoAplicacion()->MouseFocus = false;
								}
							}

							//si cambio el estado y es del teclado
							if(E.active.state & SDL_APPINPUTFOCUS)
							{
								//si gano foco del teclado
								if(E.active.gain)
								{
									//levanto el flag
									APP.getAplicacionGrafica()->getEstadoAplicacion()->KeyboardFocus = true;
								}
								else
								{
									//lo bajo
									APP.getAplicacionGrafica()->getEstadoAplicacion()->KeyboardFocus = false;
								}
							}

							//salir de switch
							break;
						}

					//se presiono una tecla
					case SDL_KEYDOWN:
						{
							//obtengo el estado de las teclas
							Keys = SDL_GetKeyState(NULL);
							break;
						}
				}
			}
			else //no se captaron eventos
			{
				//si la aplicacion no esta visible
				if(!APP.getAplicacionGrafica()->getEstadoAplicacion()->Visible)
				{
					//blockea el hilo hasta q se produsca un evento,
					//para no consumir loops prosesamiento q no se muestra
					SDL_WaitEvent(NULL);
				}
				else
				{
					//obtengo tiempo actual
					TickCount = SDL_GetTicks();
					//Updateo, enviendo el intervalo entre loops
					APP.Update(TickCount-LastCount, Keys);
					//el ultimo tiempo, pasa a ser el actual
					LastCount = TickCount;
					//llamo a la funcion de dibujo en pantalla
					APP.getAplicacionGrafica()->Draw(APP.getScreen());
					//intercambio los buffers (doble buffering)
					SDL_GL_SwapBuffers();
				}
			}
			usleep(10000);
		}
		//el programa esta finalizando

		//finalizo, libero recursos
		APP.getAplicacionGrafica()->Deinitialize();
		///////////////////////////////////////////////////////////////////////
		//cliente_del_modelo.join();
		//////////////////////////////////////////////////////////////////////

	}
	catch(std::runtime_error &e){
		std::cerr << e.what() << "\n";
	}
	return 0;
}
