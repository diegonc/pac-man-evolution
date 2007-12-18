#include "Aplicacion.h"

//Inicializa el contador de tiempo, utilizado para los refrescos
bool Aplicacion::InitTimers(Uint32 *C)
{
    //obtiene el tiempo actual.
	*C = SDL_GetTicks();

	return true;
}

void Aplicacion::VerificarAbecedarioMensaje(Uint8 *Keys){
    //si recibo Teclas
    char a='a';
    if(Keys)
	{
	    for (int i=SDLK_a;i<=SDLK_z;++i){
            	if(Keys[i]){
                    char letra=(char)(i-(int)SDLK_a+(int)a);
                    MensajeAEnviar.append(1,letra);
	            Keys[i]=0;
                }
	    }

	    if(Keys[SDLK_SPACE]){
                MensajeAEnviar.append(1,' ');
	       Keys[SDLK_SPACE]=0;
	    }

	    if(Keys[SDLK_BACKSPACE]){
		if (MensajeAEnviar.length()>0)
	                MensajeAEnviar.erase(MensajeAEnviar.length()-1);
	       Keys[SDLK_BACKSPACE]=0;
	    }
		getAplicacionGrafica()->MensajeAEnviar=MensajeAEnviar;
        //si la tecla escape fue presionada

	}
}

//actualiza el modelo visual segun los eventos de teclado recibidos
void Aplicacion::Update(Uint32 Milliseconds, Uint8 *Keys)
{
    //si recibo Teclas
    if(Keys)
	{
        //si la tecla escape fue presionada
		if(Keys[SDLK_ESCAPE])
		{
		    //terminar aplicacion
			TerminateApplication();
		}

        //si la tecla F1 fue presionada
		if(Keys[SDLK_F1])
		{
		    //cambio ModoVentana
			ToggleFullscreen();
		}

		if (!EscribiendoMensaje){

		    if(Keys[SDLK_c]){
		        getAplicacionGrafica()->CambiarCamara();
		        Keys[SDLK_c]=0;
		    }

		    if(Keys[SDLK_y]){
		        EscribiendoMensaje=true;
		        MensajeAEnviar="";
		        Keys[SDLK_y]=0;
		    }
		}else{
	          VerificarAbecedarioMensaje(Keys);
        	    if(Keys[SDLK_RETURN]){
        	        EscribiendoMensaje=false;
//			std::cout << "Aca se deberia enviar el mensaje: " << MensajeAEnviar  << std::endl;
			//getAplicacionGrafica()->MensajeAMostrar=MensajeAEnviar;
			S_ptr<Paquete> PaqMens(new PaqueteMensaje(MensajeAEnviar));
			cliente->get_escritor().encolar_paquete(PaqMens);
			getAplicacionGrafica()->MensajeAEnviar="";
        	        Keys[SDLK_RETURN]=0;
        	    }			
	        }

		//si se apreto arriba
		if(Keys[SDLK_UP]){
		    //creo una instancia de Key correspondiente a ARRIBA
			S_ptr<Paquete> PaqTec(new PaqueteTecla(JugadorLocal::get_instancia()->get_id(),0));
			cliente->get_escritor().encolar_paquete(PaqTec);
		    //kop.ejecutar(*(getAplicacionGrafica()->getModelo()));

            //bajo el flag
            Keys[SDLK_UP]=0;
        }

        //si se apreto abajo
        if(Keys[SDLK_DOWN]){
            //creo una instancia de Key correspondiente a ABAJO
            S_ptr<Paquete> PaqTec(new PaqueteTecla(JugadorLocal::get_instancia()->get_id(),2));
            cliente->get_escritor().encolar_paquete(PaqTec);
		    //kop.ejecutar(*(getAplicacionGrafica()->getModelo()));
            //bajo el flag
            Keys[SDLK_DOWN]=0;
        }

        //lo mismo si izq
        if(Keys[SDLK_LEFT]){
            //KeyOp kop(JugadorLocal::get_id(),3);
		    //kop.ejecutar(*ModeloServidor::get_instancia());

            S_ptr<Paquete> PaqTec(new PaqueteTecla(JugadorLocal::get_instancia()->get_id(),3));
            cliente->get_escritor().encolar_paquete(PaqTec);
            Keys[SDLK_LEFT]=0;

        }

        //lo mismo si derecha
        if(Keys[SDLK_RIGHT]){
            S_ptr<Paquete> PaqTec(new PaqueteTecla(JugadorLocal::get_instancia()->get_id(),1));
            cliente->get_escritor().encolar_paquete(PaqTec);
            Keys[SDLK_RIGHT]=0;
        }
	}
}

//terminar aplicacion
void Aplicacion::TerminateApplication()
{
    //evento q enviamos
	static SDL_Event Q;
    //definimos el tipo de evento
	Q.type = SDL_QUIT;

    //Mando el Evento de Quit
	SDL_PushEvent(&Q);
}

//intercambiar modo de ventana
void Aplicacion::ToggleFullscreen()
{
    //Superficie
	SDL_Surface *S;
    //obtengo la superficie de Video
	S = SDL_GetVideoSurface();

    //cambio a fullscreen
	SDL_WM_ToggleFullScreen(S);
}

//redibujar para mover y resize
void Aplicacion::ReshapeGL(int width, int height)
{
    //reseteo la vista
	glViewport(0,0,(GLsizei)(width),(GLsizei)(height));
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

    //calculo la vista para el tamanio de la ventana
	gluPerspective(45.0f,(GLfloat)(width)/(GLfloat)(height),1.0f,100.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

//crear ventana
bool Aplicacion::CreateWindowGL(int W, int H, int B, Uint32 F)
{
    //seteo atributos
	SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 5 );
	SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 5 );
	SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 5 );
	SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 16 );
	SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );


    //creo la ventana
	if(!(Screen = SDL_SetVideoMode(W, H, B, F)))
	{
		return false;
	}

    //agrego el canal alfa
	SDL_FillRect(Screen, NULL, SDL_MapRGBA(Screen->format,0,0,0,0));

    //redibujo
	ReshapeGL(SCREEN_W, SCREEN_H);

	return true;
}

//Carga BMP desde path en una superficie, para icono del programa
SDL_Surface* Aplicacion::SetUpIcon(char *File)
{
    //superficie
	SDL_Surface *Icon;
	Uint8       *Pixels, *Mask;
	int         i, mlen;

    //cargo el bmp
	Icon = SDL_LoadBMP(File);

    //seteo el color key, para transparencia
	SDL_SetColorKey(Icon, SDL_SRCCOLORKEY, *((Uint8 *)Icon->pixels));

    // Point the raw data
	Pixels =(Uint8 *)Icon->pixels;
    // And calculate the total size
	mlen   = Icon->w*Icon->h;

	Mask = (Uint8 *)malloc(mlen/8);

    // Zero the memory
	memset(Mask, 0, mlen/8);

    // Do the icon masking
	for(i=0;i<mlen;)
	{
        // More info on this
		if(Pixels[i] != *Pixels)
		{
		    // on the SDL docs
			Mask[i/8] |= 0x01;
		}

		++i;

		if((i%8)!=0)
		{
			Mask[i/8] <<= 1;
		}
	}

    // Seteo el icono a la ventana
	SDL_WM_SetIcon(Icon, Mask);

	return Icon;
}
