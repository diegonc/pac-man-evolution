
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
#include <math.h>
#include <map>

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
SDL_Surface *SD_Logo;											// ...and a SD Logo
bool        EsceneCreado=false;
GLuint      Escenario;
obj_type Pacman;
std::map<std::string,obj_type> Cosas;


// Code



bool InitGL(SDL_Surface *S)										// Any OpenGL Initialization Code Goes Here
{
	glClearColor(0.0f,0.0f,0.0f,0.5f);							// Black Background
	glClearDepth(1.0f);											// Depth Buffer Setup
	glDepthFunc(GL_LEQUAL);										// The Type Of Depth Testing (Less Or Equal)
	glEnable(GL_DEPTH_TEST);									// Enable Depth Testing
	glShadeModel(GL_SMOOTH);									// Select Smooth Shading
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);			// Set Perspective Calculations To Most Accurate

	return true;												// Return TRUE (Initialization Successful)
}

void DibujarObjeto(obj_type* object){
    float const proporcion=0.04;

    glScalef( proporcion, proporcion, proporcion);
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
    glScalef( 1/proporcion, 1/proporcion, 1/proporcion);
}

void CargarCosas(){
    obj_type Cosa;
    Load3DS(&Cosa,"banana.3DS");
    Cosas["banana"]=Cosa;
    Load3DS(&Cosa,"pacman.3DS");
    Cosas["pacman"]=Cosa;
    Load3DS(&Cosa,"spaceship.3DS");
    Cosas["spaceship"]=Cosa;

}


bool Initialize(void)											// Any Application & User Initialization Code Goes Here
{
    //Load3DS(&Pacman,"banana.3DS");
    CargarCosas();
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

void Update(Uint32 Milliseconds, Uint8 *Keys,Posicion* Pos)					// Perform Motion Updates Here
{
    Pos->girar(Milliseconds);
    const float Vel=0.4/40;
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
		    Pos->Velocid+=Vel;

            Keys[SDLK_UP]=0;
        }

        if(Keys[SDLK_DOWN]){
            Pos->Velocid=0;
            Keys[SDLK_DOWN]=0;
        }

        if(Keys[SDLK_LEFT]){

            Pos->girarIzquierda();
            Keys[SDLK_LEFT]=0;
        }

        if(Keys[SDLK_RIGHT]){
            Pos->girarDerecha();
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

void Desplazar(float delta, Posicion* Pos){
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

void Draw(SDL_Surface *Screen,Posicion* P)									// Our Drawing Code
{
	assert(Screen);												// We won't go on if the Screen pointer is invalid

	Draw3D(Screen,P);												// We split our drawing code into two pieces:
	//Draw2D(Screen);												// First draw the 3d stuff, then blit 2d surfaces onto it

	return;
}

void addPared(float xIn,float xFin,float yIn,float yFin){
    glBegin(GL_QUADS);
      glVertex3f(xIn, yIn, 0.0);
      glVertex3f(xFin, yFin,0.0);
      glVertex3f(xFin, yFin, 2.0);
      glVertex3f(xIn, yIn, 2.0);
    glEnd();

}


void addPiso(double xIn,double xFin,double yIn,double yFin){
    glBegin(GL_QUADS);
      glVertex3f(xIn, yIn, 0.0);
      glVertex3f(xFin, yIn, 0.0);
      glVertex3f(xFin, yFin, 0.0);
      glVertex3f(xIn, yFin,0.0);
    glEnd();
}

void DrawEscenario(){

    glColor3f(1, 1, 0);  /* amarillo */
    addPiso(-2,2,-10,10);
    glColor3f(1, 1, 0);  /* amarillo */
    addPiso(-10,10,10,14);

    glColor3f(1, 1, 1);  /* blanco */
    addPared(-10,10,14,14);
    glColor3f(0.0, 0.0, 1);  /* blue */
    addPared(-10,-2,10,10);
    glColor3f(0.0, 0.0, 1);  /* blue */
    addPared(2,10,10,10);

    glColor3f(0.0, 0.7, 0.1);  /* green */
    addPared(-2,-2,-10.0,10.0);
    glColor3f(1.0, 0.0, 0.0);  /* Red */
    addPared(2,2,-10.0,10.0);
}

void DibujarObjetoObservadorPosicion(Posicion* P,std::string Nombre){
    float Angulo=P->getAnguloActual();
    Angulo=(Angulo/180)*3.14;
    float deltaX=sin(Angulo);
    float deltaY=cos(Angulo);
    //printf("%d\n",P->getAnguloActual());
    //glTranslatef(P->x,P->y, 0.0);


    //glTranslatef(-P->x, -P->y, 0.0);

    glRotatef(P->getAnguloActual(), 0, 0, 1.0);

    //glTranslatef(P->x, P->y, 0.0);

  //  glTranslatef(P->x,P->y, 0.0);

    DibujarObjeto(&Cosas[Nombre]);
    glTranslatef(P->x,P->y, 0.0);

    //gluLookAt( GLdouble eyeX,GLdouble eyeY,GLdouble eyeZ,GLdouble centerX,GLdouble centerY,GLdouble centerZ,GLdouble upX,GLdouble upY,GLdouble upZ )
//    gluLookAt(-deltaX,-deltaY,-1,0,0,0,deltaX,deltaY,0);
   // glTranslatef(-deltaX,-deltaY, 0.0);



//    glTranslatef(deltaX,deltaY, 0.0);
    //glRotatef(P->getAnguloActual(), 0, 0, 1.0);



    //glRotatef(-P->getAnguloActual(), 0, 0, 1.0);
    //glTranslatef(P->x,P->y, 0.0);
    //glRotatef(P->getAnguloActual(), 0, 0, 1.0);
//    glTranslatef(deltaX,deltaY, 0.0);
//    glTranslatef(P->x,P->y, 0.0);

//    glTranslatef(P->x,P->y, 0.0);
    //glTranslatef(P->x,P->y, 0.0);

}

void DibujarObjetoPosicion(Posicion* P,std::string Nombre){
    glTranslatef(P->x,P->y, 0.0);
    DibujarObjeto(&Cosas[Nombre]);
    glTranslatef(-P->x,-P->y, 0.0);
}

void Draw3D(SDL_Surface *S,Posicion* P)										// OpenGL drawing code here
{
    //glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		// Clear Screen And Depth Buffer
	//glLoadIdentity();
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		// Clear Screen And Depth Buffer

    glMatrixMode(GL_MODELVIEW);

    /* reset modelview matrix to the identity matrix */
    glLoadIdentity();




    //lo llevo a 1ra persona
    glRotatef(-90, 1, 0.0, 0.0);
    glTranslatef(0.0,0.0 , -2.5);
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

    /*for (list<Objetos>::iterator it=listaObjetos.begin();it!=listaObjetos.end();++it){
	    DibujarObjetoPosicion(it->Pos,it->tipo);
    }*/

	glColor3f(0.2,0.2,1);



	//DibujarObjetoPosicion(&Pos,"banana");

	DibujarObjetoObservadorPosicion(P,"banana");
	Posicion Pos;
	Pos.x=0;
	Pos.y=10;
	DibujarObjetoPosicion(&Pos,"banana");
	Pos.x=3;
	Pos.y=12;
	DibujarObjetoPosicion(&Pos,"banana");



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
