
/**************************************
*                                     *
*   Jeff Molofee's Basecode Example   *
*   SDL porting by Fabio Franchello   *
*          nehe.gamedev.net           *
*                2001                 *
*                                     *
**************************************/

// Includes
//#ifdef WIN32													// If We're Under MSVC
//#include <windows.h>											// Include The Windows Header
//#else															// Otherwise
#include <stdio.h>												// Include The Standar IO Header
#include <stdlib.h>												// And The Standard Lib (for exit())
//#endif															// Then...

#include <math.h>												// We Require The Math Lib For Sin and Cos
#include <GL/gl.h>												// And Obviously The OpenGL Header
#include <GL/glu.h>												// And The GLu Heander

#include <SDL.h>												// Finally: The SDL Header!
#include <assert.h>
#include "3dsloader.h"
#include "ObjetoVisual.h"

#include "main.h"												// We're Including theHeader Where Defs And Prototypes Are
#include <iostream>
#include <string>
#include <math.h>
#include <map>
#include <list>
#include "../../server/ModeloServidor.h"
#include "../../server/KeyOp.h"

//#ifdef WIN32													// If We're Under MSVC
//#pragma comment( lib, "OpenGL32.lib" )							// We Can Tell The Linker To Look For OpenGl32.lib ...
//#pragma comment( lib, "GLu32.lib" )								// ...GLu32.lib ...
//#pragma comment( lib, "SDLmain.lib" )							// ...SDLmain.lib ...
//#pragma comment( lib, "SDL.lib" )								// And SDL.lib At Link Time
//#endif															// For Other Platforms, Such As LINUX, The Link Flags Are Defined in The Makefile


extern S_AppStatus AppStatus;									// We're Using This Struct As A Repository For The Application State (Visible, Focus, ecc)

// User Defined Variables
float		angle;												// Used To Rotate The Triangles
float		cnt1, cnt2;											// Used To Move The Object On The Screen
float		Lx, Ly;												// We use all this variables to hold
Sint16		Ix, Iy;												// Values used for moving/rotating figures
int			rot1, rot2;											// Counter Variables
Sint16		IyOff, IxOff;										// Counter Variavles
SDL_Surface *NeHe_Logo;											// We have 3 logo: an NeHe Logo...
SDL_Surface *SDL_Logo;											// ...an SDL Logo...
SDL_Surface *SD_Logo;
											// ...and a SD Logo
bool        EsceneCreado=false;
GLuint      Escenario;
std::map<std::string,ObjTextura*> Cosas;
GLuint texturaPiso;
GLuint texturaPared;

ModeloServidor mod;



// Code



bool InitGL(SDL_Surface *S)										// Any OpenGL Initialization Code Goes Here
{
	glClearColor(0.0f,0.0f,0.0f,0.5f);							// Black Background
	glClearDepth(1.0f);											// Depth Buffer Setup
	glDepthFunc(GL_LEQUAL);										// The Type Of Depth Testing (Less Or Equal)
	glEnable(GL_DEPTH_TEST);									// Enable Depth Testing
	glShadeModel(GL_SMOOTH);									// Select Smooth Shading
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable( GL_TEXTURE_2D ); // Need this to display a texture
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);			// Set Perspective Calculations To Most Accurate
    mod.start();
	return true;												// Return TRUE (Initialization Successful)

}

void DibujarObjeto(ObjTextura* objTex){
    GLuint* texture=&objTex->textura;




    float const proporcion=0.04;
    obj_type* object;
    //float color[4]={0.1,0.3,0.5,1};
    // Bind the texture object
    glBindTexture( GL_TEXTURE_2D, *texture );
/////////////opacidad
//glColor4f( 1, 1, 1, 1.0f ); // aca le decimos que module la textura con negro, por lo tanto donde dibuje tan solo oscurecera, y que al alpha lo divida por la mitad.
//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//glEnable(GL_BLEND);
//glDisable(GL_DEPTH_TEST);
/////////////ENDDDDDDDDopacidad
glScalef( proporcion, proporcion, proporcion);

    //glShadeModel( GL_FLAT );

    //glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color );


    for (std::list<obj_type_ptr>::iterator it=objTex->Objeto3d.Figuras.begin();it!=objTex->Objeto3d.Figuras.end();++it){
        object=*it;

        glBegin(GL_TRIANGLES); // glBegin and glEnd delimit the vertices that define a primitive (in our case triangles)
        for (int l_index=0;l_index<object->polygons_qty;l_index++)
        {
            //----------------- FIRST VERTEX -----------------
            // Texture coordinates of the first vertex

            glTexCoord2f( object->mapcoord[ object->polygon[l_index].a ].u,
                          object->mapcoord[ object->polygon[l_index].a ].v);
            // Coordinates of the first vertex

            glVertex3f( object->vertex[ object->polygon[l_index].a ].x,
                        object->vertex[ object->polygon[l_index].a ].y,
                        object->vertex[ object->polygon[l_index].a ].z); //Vertex definition

            //----------------- SECOND VERTEX -----------------
            // Texture coordinates of the second vertex
            glTexCoord2f( object->mapcoord[ object->polygon[l_index].b ].u,
                          object->mapcoord[ object->polygon[l_index].b ].v);
            // Coordinates of the second vertex
            glVertex3f( object->vertex[ object->polygon[l_index].b ].x,
                        object->vertex[ object->polygon[l_index].b ].y,
                        object->vertex[ object->polygon[l_index].b ].z);

            //----------------- THIRD VERTEX -----------------
            // Texture coordinates of the third vertex
            glTexCoord2f( object->mapcoord[ object->polygon[l_index].c ].u,
                          object->mapcoord[ object->polygon[l_index].c ].v);
            // Coordinates of the Third vertex
            glVertex3f( object->vertex[ object->polygon[l_index].c ].x,
                        object->vertex[ object->polygon[l_index].c ].y,
                        object->vertex[ object->polygon[l_index].c ].z);
        }
        glEnd();
    }


glScalef( 1/proporcion, 1/proporcion, 1/proporcion);
//glDisable(GL_BLEND);
//glEnable(GL_DEPTH_TEST);




    glBindTexture( GL_TEXTURE_2D, 0 );






}

void CargarTextura(GLuint* texture,std::string nombrearchBMP){
// Load the OpenGL texture

    SDL_Surface *surface; // Gives us the information to make the texture

    if ( (surface = SDL_LoadBMP(nombrearchBMP.c_str())) ) {

        // Check that the image's width is a power of 2
        if ( (surface->w & (surface->w - 1)) != 0 ) {
            printf("warning: image.bmp's width is not a power of 2\n");
        }

        // Also check if the height is a power of 2
        if ( (surface->h & (surface->h - 1)) != 0 ) {
            printf("warning: image.bmp's height is not a power of 2\n");
        }

        // Have OpenGL generate a texture object handle for us
        glGenTextures( 1, texture );

        glBindTexture (GL_TEXTURE_2D, *texture);

        // Set the texture's stretching properties
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        // Edit the texture object's image data using the information SDL_Surface gives us
        glTexImage2D( GL_TEXTURE_2D, 0, 3, surface->w, surface->h, 0,
                      GL_BGR, GL_UNSIGNED_BYTE, surface->pixels );
    }
    else {
        printf("SDL could not load image.bmp: %s\n", SDL_GetError());
        //SDL_Quit();
        //return 1;
    }

    // Free the SDL_Surface only if it was successfully created
    if ( surface ) {
        SDL_FreeSurface( surface );
    }
    glBindTexture (GL_TEXTURE_2D, 0);
}

void CargarCosas(){
    ObjTextura* objtext=new ObjTextura;
        Load3DS(&(objtext->Objeto3d),"banana.3DS");
        CargarTextura(&(objtext->textura),"banana.bmp");
        Cosas["banana"]=objtext;
    objtext=new ObjTextura;
        Load3DS(&(objtext->Objeto3d),"pacman.3DS");
        CargarTextura(&(objtext->textura),"pacman.bmp");
        Cosas["pacman"]=objtext;
    objtext=new ObjTextura;
        Load3DS(&(objtext->Objeto3d),"pastilla.3DS");
        CargarTextura(&(objtext->textura),"pastilla.bmp");
        Cosas["pastilla"]=objtext;
    objtext=new ObjTextura;
        Load3DS(&(objtext->Objeto3d),"cerecita.3DS");
        CargarTextura(&(objtext->textura),"cerecita.bmp");
        Cosas["cerecita"]=objtext;
    objtext=new ObjTextura;
        Load3DS(&(objtext->Objeto3d),"fantasma.3DS");
        CargarTextura(&(objtext->textura),"fantasma.bmp");
        Cosas["fantasma"]=objtext;
    objtext=new ObjTextura;
        Load3DS(&(objtext->Objeto3d),"powerup.3DS");
        CargarTextura(&(objtext->textura),"powerup.bmp");
        Cosas["powerup"]=objtext;

}



bool Initialize(void)											// Any Application & User Initialization Code Goes Here
{
    //Load3DS(&Pacman,"banana.3DS");
    CargarCosas();
    CargarTextura(&texturaPared,"pared.bmp");
    CargarTextura(&texturaPiso,"piso.bmp");
    AppStatus.Visible		= true;								// At The Beginning, Our App Is Visible
	AppStatus.MouseFocus	= true;								// And Have Both Mouse
	AppStatus.KeyboardFocus = true;								// And Input Focus

	// Start Of User Initialization
	angle		= 0.0f;											// Set The Starting Angle To Zero
	cnt1		= 0.0f;											// Set The Cos(for the X axis) Counter To Zero
	cnt2		= 0.0f;											// Set The Sin(for the Y axis) Counter To Zero
	Lx			= 0.0f;
	Ly			= 0.0f;
	Iy			= 0;
	Ix			= 0;
	IyOff		= 1;
	IxOff		= 1;

	if(!(NeHe_Logo = SDL_LoadBMP("NeHe_Title.bmp")) ||			// We try to load the first...
		!(SDL_Logo = SDL_LoadBMP("SDL_Title.bmp")) ||			// ...the second...
		!(SD_Logo = SDL_LoadBMP("SD_Title.bmp")) )				// ..and the third Logo
	{
		Log("Cannot load graphic: %s\n", SDL_GetError() );
		return false;
	}

	SDL_SetColorKey(NeHe_Logo, SDL_SRCCOLORKEY|SDL_RLEACCEL,	// Now: we're setting the key color for
		SDL_MapRGB(NeHe_Logo->format, 0, 0, 0) );				// the logo surfaces. That is the color that
	SDL_SetColorKey(SDL_Logo, SDL_SRCCOLORKEY|SDL_RLEACCEL,		// we want to result traslucent when the
		SDL_MapRGB(SDL_Logo->format, 0, 0, 0) );				// surface is blit. Refer on the SDL docs
	SDL_SetColorKey(SD_Logo, SDL_SRCCOLORKEY|SDL_RLEACCEL,		// for more info about this
		SDL_MapRGB(SD_Logo->format, 0, 0, 0) );					// topic.

	return true;												// Return TRUE (Initialization Successful)
}


void Deinitialize(void)											// Any User Deinitialization Goes Here
{
	return;														// We Have Nothing To Deinit Now
}

void Update(Uint32 Milliseconds, Uint8 *Keys,Posicion_Graf* Pos)					// Perform Motion Updates Here
{
    Pos->girar(Milliseconds);
    const float Vel=0.01;
	if(Keys)													// If We're Sent A Key Event With The Update
	{
		if(Keys[SDLK_ESCAPE])									// And If The Key Pressed Was ESC
		{
			TerminateApplication();								// Terminate The Application
		}

		if(Keys[SDLK_F1])										// If The Key Pressed Was F1
		{
			ToggleFullscreen();									// Use SDL Function To Toggle Fullscreen Mode (But Not In Windows :) )
		}

		if(Keys[SDLK_UP]){
		    KeyOp kop(1,0);
		    kop.ejecutar(mod);
		    //Pos->Velocid+=Vel;

            Keys[SDLK_UP]=0;
        }

        if(Keys[SDLK_DOWN]){
            KeyOp kop(1,2);
		    kop.ejecutar(mod);
//            Pos->Velocid=0;
            Keys[SDLK_DOWN]=0;
        }

        if(Keys[SDLK_LEFT]){
            KeyOp kop(1,3);
		    kop.ejecutar(mod);
            //Pos->girarIzquierda();
            Keys[SDLK_LEFT]=0;
        }

        if(Keys[SDLK_RIGHT]){
            KeyOp kop(1,1);
		    kop.ejecutar(mod);
            //Pos->girarDerecha();
            Keys[SDLK_RIGHT]=0;
        }
	}
    Desplazar(Milliseconds * Pos->Velocid,Pos);
	//angle += (float)(Milliseconds) / 5.0f;						// Update Angle Based On The Clock
	//cnt1  += 0.010f;											// Update the Cos Counter Based On The Clock
	//cnt2  += 0.008f;											// And The Same Thing For The Sin Counter
	//Lx    += 0.035f;
	//Ly    += 0.030f;

	return;														// We Always Make Functions Return
}

void Desplazar(float delta, Posicion_Graf* Pos){
    if (Pos->getAnguloActual()==0){
        Pos->y -= delta;
    }else if (Pos->getAnguloActual()==90){
        Pos->x -= delta;
    }else if (Pos->getAnguloActual()==180){
        Pos->y += delta;
    }else if (Pos->getAnguloActual()==270){
        Pos->x += delta;
    }else{
        //throw "Angulo Invalido";
    }
}

int getAnguloDireccion(Direccion &dir){
    switch (dir.get_dir()){
        case (0): //nortee
            return 180; //alan te odioo//return 0;
        case (1):
            return 270;
        case (2):
            return 0;
        case (3):
            return 90;
    }
}

void Draw(SDL_Surface *Screen,Posicion_Graf* P)									// Our Drawing Code
{
	assert(Screen);												// We won't go on if the Screen pointer is invalid

	Draw3D(Screen,P);												// We split our drawing code into two pieces:
	//Draw2D(Screen);												// First draw the 3d stuff, then blit 2d surfaces onto it

	return;
}

void addPared(float xIn,float xFin,float yIn,float yFin){//,float color[]){
    //glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color );
    glBindTexture (GL_TEXTURE_2D, texturaPared);
    float const AltoPasillo=3;
    float const DimImagen=4;
    float VecesLargo;
    float VecesAlto=AltoPasillo/DimImagen;
    if (xIn==xFin){
        VecesLargo=abs((int)(yIn-yFin))/DimImagen;
    }else{
        VecesLargo=abs((int)(xIn-xFin))/DimImagen;
    }

    glBegin(GL_QUADS);
      glTexCoord2f( 0, 0 );
      glVertex3f(xIn, yIn, 0.0);
      glTexCoord2f( VecesLargo, 0 );
      glVertex3f(xFin, yFin,0.0);
      glTexCoord2f( VecesLargo, VecesAlto);
      glVertex3f(xFin, yFin, AltoPasillo);
      glTexCoord2f( 0, VecesAlto);
      glVertex3f(xIn, yIn, AltoPasillo);
    glEnd();
    glBindTexture (GL_TEXTURE_2D, 0);
}


void addPiso(double xIn,double xFin,double yIn,double yFin){//,float color[]){
    //glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color );
    glBindTexture (GL_TEXTURE_2D, texturaPiso);
    float const DimImagen=1.5;
    float VecesAncho=abs((int)(xIn-xFin))/DimImagen;
    float VecesLargo=abs((int)(yIn-yFin))/DimImagen;


    glBegin(GL_QUADS);
      glTexCoord2f( 0, 0 );
      glVertex3f(xIn, yIn, 0.0);
      glTexCoord2f( VecesAncho, 0 );
      glVertex3f(xFin, yIn, 0.0);
      glTexCoord2f( VecesAncho, VecesLargo );
      glVertex3f(xFin, yFin, 0.0);
      glTexCoord2f( 0, VecesLargo );
      glVertex3f(xIn, yFin,0.0);
    glEnd();
    glBindTexture (GL_TEXTURE_2D, 0);
}

void DrawEscenario(){
    typedef std::list<S_ptr<EstructuralUnitario> > listaEstruc;
    listaEstruc Estructurales=mod.get_mundo().get_mapa_activo().get_estructurales();
    S_ptr<EstructuralUnitario> est;
    S_ptr<EstructuralUnitario> vecino;
    Posicion PosEst;
    float xIn;
    float xFin;
    float yIn;
    float yFin;

    for (listaEstruc::iterator it=Estructurales.begin();it!=Estructurales.end();++it){
        est=*it;
        PosEst=est->get_posicion();
        vecino=est->get_arriba();

        xIn=-PosEst.get_x()*4;
        xFin=xIn-4;
        yIn=PosEst.get_y()*4;
        yFin=yIn+4;

        if (vecino.es_nulo()){
            addPared(xIn,xFin,yIn,yIn);
        }
        vecino=est->get_abajo();
        if (vecino.es_nulo()){
            addPared(xIn,xFin,yFin,yFin);
        }
        vecino=est->get_izquierda();
        if (vecino.es_nulo()){
            addPared(xIn,xIn,yIn,yFin);
        }
        vecino=est->get_derecha();
        if (vecino.es_nulo()){
            addPared(xFin,xFin,yIn,yFin);
        }

        addPiso(xIn,xFin,yIn,yFin);
        printf("(%f, %f)->",xIn,yIn);
        printf("(%f, %f)\n",xFin,yFin);
    }


    //addPiso(-10,10,10,14);
    /*
    addPared(-10,10,14,14);
    //glColor3f(0.0, 0.0, 1);
    addPared(-10,-2,10,10);
    //glColor3f(0.0, 0.0, 1);
    addPared(2,10,10,10);

    //glColor3f(0.0, 0.7, 0.1);
    addPared(-2,-2,-10.0,10.0);
    //glColor3f(1.0, 0.0, 0.0);
    addPared(2,2,-10.0,10.0);
    */
}

void DibujarObjetoObservadorPosicion(Posicion_Graf* P,std::string Nombre){
  //  float Angulo=P->getAnguloActual();
 //   Angulo=(Angulo/180)*3.14;
//    float deltaX=sin(Angulo)*2;
 //   float deltaY=cos(Angulo)*2;
    float static j=0;

    if (P->Velocid!=0.0){
        j+=0.02*(P->Velocid/0.01);
    }
    float Angulo=sin(j)*7;

    glRotatef(Angulo,0,1,0);
    DibujarObjeto(Cosas[Nombre]);
    glRotatef(-Angulo,0,0,0);
    glRotatef(P->getAnguloActual(), 0, 0.0, 1.0);


    glTranslatef(P->x,P->y, 0.0);

    //glTranslatef(-deltaX,-deltaY, 0.0);
    //gluLookAt(P->x+deltaX, P->y+deltaY, 0, P->x, P->y, 0.0, 0.0, 1.0, 0.0);
}

void DibujarObjetoPosicion(Posicion_Graf* P,std::string Nombre){

    glTranslatef(P->x,P->y, 0.0);
    glRotatef(P->getAnguloActual(), 0, 0, 1.0);
    DibujarObjeto(Cosas[Nombre]);
    glRotatef(-P->getAnguloActual(), 0, 0, 1.0);
    glTranslatef(-P->x,-P->y, 0.0);

}

void Draw3D(SDL_Surface *S,Posicion_Graf* P)										// OpenGL drawing code here
{
    static float j=0;
    j+=0.003;
    //glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		// Clear Screen And Depth Buffer
	//glLoadIdentity();
    glPushMatrix();		// Apila la transformación geométrica actual
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		// Clear Screen And Depth Buffer

    glMatrixMode(GL_MODELVIEW);

    /* reset modelview matrix to the identity matrix */
    glLoadIdentity();



   //lo llevo a 1ra persona
  // glRotatef(-90, 1, 0.0, 0.0);

//////LUZZZZZZZZZ
    static GLfloat pos[4] = {0, 0, 1, 0 };
    glLightfv( GL_LIGHT0, GL_POSITION, pos );

//   glTranslatef(0.0,15 , -6);
   //VistaUP
   glTranslatef(0,0 , -20);


//END LUZ





    //glLightfv( GL_LIGHT0, GL_SPOT_DIRECTION, pos );
//    float color[4]={1,1,1,0.3};
 //   glLightModelfv( GL_LIGHT_MODEL_AMBIENT, color);

    //glTranslatef(0.0,0.0 , -20);
    //avanzarr
    //glTranslatef(P->x, P->y, 0.0);

    //glTranslatef(-P->x, -P->y, 0.0);

    //glTranslatef(P->x, P->y, 0.0);


	//glLoadIdentity();
	if (!EsceneCreado){
	    EsceneCreado=true;
	   Escenario = glGenLists (1);
       glNewList(Escenario, GL_COMPILE);
    //   torus(8, 25);
        DrawEscenario();
       glEndList();
	}

   std::list< S_ptr<Jugador> >::const_iterator jugadores;
   S_ptr<Jugador> jp;
   for(jugadores = mod.get_jugadores().begin();jugadores != mod.get_jugadores().end(); ++jugadores){
       jp = *jugadores;
       if(jp->get_id() == 1){
            Posicion p=jp->get_posicion();
            P->x=p.get_x()*4;
            P->y=-p.get_y()*4;
            P->setAnguloActual(getAnguloDireccion(jp->get_direccion()));
            DibujarObjetoObservadorPosicion(P,"pacman");
       }
       else{
/*         Posicion p=jp->get_posicion();
         P->x=p.get_x()*4;
         P->y=-p.get_y()*4;
         P->setAnguloActual(getAnguloDireccion(jp->get_direccion()));
         DibujarObjetoPosicion(P,"fantasma");*/
        
         Posicion_Graf Pos;
	      Posicion p2=jp->get_posicion();
      	Pos.x= -p2.get_x()*4;
         Pos.y= p2.get_y()*4;
      	DibujarObjetoPosicion(&Pos,"fantasma");
      }  
   }
   std::list< S_ptr<Comestible> > lista_comestibles = mod.get_mundo().get_mapa_activo().get_comestibles();
   std::list< S_ptr<Comestible> >::iterator comestibles;
   S_ptr<Comestible> comestible;
   
   for(comestibles = lista_comestibles.begin(); comestibles != lista_comestibles.end(); ++comestibles){
         comestible = *comestibles;         
         Posicion_Graf Pos;
         Posicion p=comestible->get_posicion();
   
      	Pos.x= -p.get_x()*4;
         Pos.y= p.get_y()*4;
      	DibujarObjetoPosicion(&Pos,"pastilla");
   }
   /*
    Pos.x=-sin(j)*10;
	Pos.y=12;

	if (cos(j)>=0){
        Pos.setAnguloActual(90);
	}else{
        Pos.setAnguloActual(-90);
    }
    DibujarObjetoPosicion(&Pos,"pacman");
*/


glCallList(Escenario);
	/*
	for (list<Objetos>::iterator it=listaObjetos.begin();it!=listaObjetos.end();++it){
	    DibujarObjetoPosicion(it->Pos,it->tipo);
    }
*/
    //glTranslatef(0.0,-2, 0.0);

	//DibujarObjeto(&Pacman);



	//glTranslatef(-P->x, -P->y+2, 0.0);
    //DibujarObjeto(&Pacman);

	return;
}

void Draw2D(SDL_Surface *S)										// SDL drawing code here
{
    /*
	static SDL_Rect src1={0,0,0,0},								// We're blitting 3 rectangles,
					src2={0,0,0,0},								// so we have to prepare them
					src3={0,0,0,0};

	SDL_FillRect(S, &src1, SDL_MapRGBA(S->format,0,0,0,0));
																// That's an issue many people is having!
																// We set up our Alpha Channel first!

	src1.x = (Sint16)((SCREEN_W+NeHe_Logo->w)/2+(cos(Lx)*170)-SCREEN_W/6);
																// src1 is the first Logo
	src1.y = (Iy+=IyOff);

	if(Iy>SCREEN_H-NeHe_Logo->h || Iy<0)						// We calculate the position of the next frame
	{
		IyOff = -IyOff;
	}

	src1.w = NeHe_Logo->w;										// Fill the rect structure
	src1.h = NeHe_Logo->h;

	SDL_BlitSurface(NeHe_Logo, NULL, S, &src1);			// And finally blit and update
	SDL_UpdateRects(S, 1, &src1);

	SDL_FillRect(S, &src2, SDL_MapRGBA(S->format,0,0,0,0));
																// The same goes for the logo 2 and 3. Alpha Channel...

	src2.x = (Ix+=IxOff);
	src2.y = (Sint16)((SCREEN_H+SDL_Logo->h)/2+(sin(Ly)*170)-SCREEN_H/6);

	if(Ix>SCREEN_W-SDL_Logo->w || Ix<0)							// Calculations...
	{
		IxOff = - IxOff;
	}

	src2.w = SDL_Logo->w;
	src2.h = SDL_Logo->h;

	SDL_BlitSurface(SDL_Logo, NULL, S, &src2);				// Blit and Update
	SDL_UpdateRects(S, 1, &src2);

	SDL_FillRect(S, &src3, SDL_MapRGBA(S->format,0,0,0,0));
																// Guess what?

	src3.x = (Sint16)((SCREEN_W+SD_Logo->w)/2+(sin(Lx)*170)-SCREEN_W/6);
	src3.y = (Sint16)((SCREEN_H+SD_Logo->h)/2+(cos(Ly)*170)-SCREEN_H/6);

	src3.w = SD_Logo->w;
	src3.h = SD_Logo->h;

	SDL_BlitSurface(SD_Logo, NULL, S, &src3);
	SDL_UpdateRects(S, 1, &src3);
*/
	return;														// We're Always Making Functions Return
}
