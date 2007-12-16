#include "AplicacionGrafica.h"
#include "JugadorLocal.h"

EstadoAplicacion* AplicacionGrafica::getEstadoAplicacion(){
      return &AppEstado;
}

void AplicacionGrafica::CambiarCamara(){
	Camara.siguiente();
}


//inicializacion de OpenGL
bool AplicacionGrafica::InitGL(SDL_Surface *S)
{
    //color de borrado del la pantalla Negro
    glClearColor(0.0f,0.0f,0.0f,0.5f);
    //seteo la profundidad de buffer
    glClearDepth(1.0f);
    //tipo de calculo de profundidad (Menor O IGUAL)
    glDepthFunc(GL_LEQUAL);
    //linea necesaria para que calculo q objeto se ve sobre q objeto, sino los dibuja en orden de aparicion
    glEnable(GL_DEPTH_TEST);
    //seteo el tipo de sombreado
    glShadeModel(GL_SMOOTH);
    //habilito el uso de luces
    glEnable(GL_LIGHTING);
    //habilito la luz del jugador
    glEnable(GL_LIGHT0);
    //habilito el uso de texturas en 2D
    glEnable( GL_TEXTURE_2D );
    //parametros para la mejor visualizacion de la perspectiva
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    //escenario.Procesar(); //<----LO COMENTE YOOOOO!!!!
	Mapa = SDL_LoadBMP("Mapa.bmp");
	ModeladorOBJ.hidratar();
	return true;

}

//inicializacion de Datos necesarios para interfase grafica
bool AplicacionGrafica::Initialize()
{
    //Inicializo Informacion de Aplicacion
    AppEstado.Visible		= true;
	AppEstado.MouseFocus	= true;
	AppEstado.KeyboardFocus = true;

	return true;
}

//finalizar y liberar recursos
void AplicacionGrafica::Deinitialize()
{
  	SDL_FreeSurface(Mapa); 
}



//get Angulo Desde Direccion
int AplicacionGrafica::getAnguloDireccion(Direccion &dir){
    //dependiendo de la direccion
    switch (dir.get_dir()){
        //norte
        case (_NORTE):
            return 180;
        //este
        case (_ESTE):
            return 270;
        //sur
        case (_SUR):
            return 0;
        //oeste
        case (_OESTE):
            return 90;
		default://<<----para que no tire warning
			return 0;
    }
}

// dibujo el modelo visual
void AplicacionGrafica::Draw(SDL_Surface *Screen)
{
	//valido q la pantala sea valida
	assert(Screen);

    //dibujo el modelo 3D
	Draw3D(Screen);
	//dibujo en 2 dimensiones
	Draw2D(Screen);
}


//dibujo el modelo 3D
void AplicacionGrafica::Draw3D(SDL_Surface *S)
{
    // Apila la transformación geométrica actual
    glPushMatrix();
	Jugador * jugador;
	jugador=ModeloServidor::get_instancia()->get_jugador(JugadorLocal::get_instancia()->get_id());
	static 	double j=0;
	if (jugador!=NULL){
	    if (jugador->get_personaje()->esta_vivo()){
		    //color de borrado del la pantalla Negro
		glClearColor(0.0f,0.0f,0.0f,0.5f);
	    }else{
		j+=0.0001;
		glClearColor((sin(500*j)+1)/4,0.0f,0.0f,0.5f);
	    }
	}
		
    //borro pantalla y buffer de profundidad
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		// Clear Screen And Depth Buffer
    //cambio a la matriz de modelo
    glMatrixMode(GL_MODELVIEW);

    //reseteo la misma cargando la ident
    glLoadIdentity();


    	Camara.ejecutar();


	if (escenario.loaded()){
		Posicion_Graf Pos;
		std::list< Jugador * > lista_jugadores = ModeloServidor::get_instancia()->get_jugadores();
		std::list< Jugador * >::const_iterator jugadores;
		Jugador * jp;
	
		//dibujo al jugador
		jp=ModeloServidor::get_instancia()->get_jugador(JugadorLocal::get_instancia()->get_id());
	
		if (jp!=NULL){
			Posicion pJ=jp->get_posicion();
			Pos.x=pJ.get_x()*4;
			Pos.y=-pJ.get_y()*4;
			Pos.setAnguloActual(getAnguloDireccion(jp->get_direccion()));
			//dibujo al objeto observador
			ModeladorOBJ.DibujarObjetoObservadorPosicion(&Pos,jp->get_personaje()->get_tipo());
		}
		
		//dibujo los demas
		for(jugadores = lista_jugadores.begin();jugadores != lista_jugadores.end(); ++jugadores){
			jp = *jugadores;
			if(jp->get_id() !=JugadorLocal::get_instancia()->get_id()){
				Posicion p2=jp->get_posicion();
				Pos.x= p2.get_x()*4;
				Pos.y= -p2.get_y()*4;
				ModeladorOBJ.DibujarObjetoPosicion(&Pos,jp->get_personaje()->get_tipo());
			}
		}

		std::list< S_ptr<Comestible> > lista_comestibles = ModeloServidor::get_instancia()->get_mundo().get_mapa_activo()->get_comestibles();
		std::list< S_ptr<Comestible> >::iterator comestibles;
		S_ptr<Comestible> comestible;

		//itero sobre los comestibles
		for(comestibles = lista_comestibles.begin(); comestibles != lista_comestibles.end(); ++comestibles){
			comestible = *comestibles;
			Posicion p=comestible->get_posicion();
			Pos.x= p.get_x()*4;
			Pos.y= -p.get_y()*4;
			ModeladorOBJ.DibujarObjetoPosicion(&Pos,comestible->get_tipo());
		}

		//llamo a la lista precompilada del Escenario
		escenario.ModelarEscenario();
//		std::cout << "<---------------------------------------------->" <<std::endl;
	}else
        usleep(1000);

}
//dibuja en 2D
void AplicacionGrafica::Draw2D(SDL_Surface *S)
{
	static SDL_Rect src1={0,0,0,0};							// We're blitting 3 rectangles,

	SDL_FillRect(S, &src1, SDL_MapRGBA(S->format,0,0,0,0));
																// That's an issue many people is having!
																// We set up our Alpha Channel first!

	src1.x = (Sint16)(800-260);
																// src1 is the first Logo
	src1.y = (Sint16)(0);

	src1.w = 260;										// Fill the rect structure
	src1.h = 260;
	SDL_SetColorKey(Mapa, SDL_SRCCOLORKEY, 
	  SDL_MapRGB(Mapa->format, 0, 0, 255));

	SDL_BlitSurface(Mapa, NULL, S, &src1);			// And finally blit and update
	SDL_UpdateRects(S, 1, &src1);

}
