#include "AplicacionGrafica.h"
#include "JugadorLocal.h"

EstadoAplicacion* AplicacionGrafica::getEstadoAplicacion(){
      return &AppEstado;
}

void AplicacionGrafica::CambiarCamara(){
	CamaraPrimeraPersona=!CamaraPrimeraPersona;
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
	//Draw2D(Screen);
}


//dibujo el modelo 3D
void AplicacionGrafica::Draw3D(SDL_Surface *S)
{
    // Apila la transformación geométrica actual
    glPushMatrix();
    //borro pantalla y buffer de profundidad
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		// Clear Screen And Depth Buffer
    //cambio a la matriz de modelo
    glMatrixMode(GL_MODELVIEW);

    //reseteo la misma cargando la ident
    glLoadIdentity();


    //seleccion de camara
    if (CamaraPrimeraPersona){
		glRotatef(-65, 1, 0.0, 0.0);
		//seteo la pos de la luz sobre el eje y
		static GLfloat pos[4] = {0, 0, 1, 0 };
		//agrego la luz (estaba habilitada (INITGL)) es una luz del tipo posicion con la pos antes mencionada
		glLightfv( GL_LIGHT0, GL_POSITION, pos );
		glTranslatef(0.0,15 , -10);
	}else{
		static GLfloat pos[4] = {0, 0, 1, 0 };
		//agrego la luz (estaba habilitada (INITGL)) es una luz del tipo posicion con la pos antes mencionada
		glLightfv( GL_LIGHT0, GL_POSITION, pos );
		glTranslatef(0,0 , -100);
	}

	if (escenario.loaded()){
		Posicion_Graf Pos;
		std::list< S_ptr<Jugador> >::const_iterator jugadores;
		S_ptr<Jugador> jp;
		//obtengo los jugadores
		//std::cout << "HERE 1 -<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n";		  
		std::cout << "Personajes:"<< ModeloServidor::get_instancia()->get_jugadores().size() << std::endl;
		for(jugadores = ModeloServidor::get_instancia()->get_jugadores().begin();jugadores != ModeloServidor::get_instancia()->get_jugadores().end(); ++jugadores){
			jp = *jugadores;
		   //si el id es 1(deberia ser jugador cliente)
		   if(jp->get_id() == JugadorLocal::get_instancia()->get_id()){
				//obtengo la posicion y la parseo
				Posicion p=jp->get_posicion();
				Pos.x=p.get_x()*4;
				Pos.y=-p.get_y()*4;
				Pos.setAnguloActual(getAnguloDireccion(jp->get_direccion()));
				//dibujo al objeto observador
				ModeladorOBJ.DibujarObjetoObservadorPosicion(&Pos,jp->get_personaje()->get_tipo());
		   }
		   else{ //son los otros jugadores
				Posicion p2=jp->get_posicion();
				Pos.x= p2.get_x()*4;
				Pos.y= -p2.get_y()*4;
				ModeladorOBJ.DibujarObjetoPosicion(&Pos,jp->get_personaje()->get_tipo());
				std::cout << "Dibujando otro personaje " << std::endl;
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
}
