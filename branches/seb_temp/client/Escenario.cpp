#include "Escenario.h"
#include <iostream>


void Escenario::ModelarEscenario(){
   if (proceso)
	glCallList(ListaEscenario);
   else
        Procesar();
}

Escenario::Escenario(){
	Cargado = false;
	proceso = false;
	primeraVez=true;
	ModeloServidor::get_instancia()->agregar_observador(this);
}

bool Escenario::loaded(){
	return Cargado;
}

void Escenario::Procesar(){
    if (primeraVez){
        CargadorDeTexturas::CargarTextura(&texturaPared,"pared.bmp");
        CargadorDeTexturas::CargarTextura(&texturaPiso,"piso.bmp");
        primeraVez=false;
    }
    ListaEscenario = glGenLists (1);
    glNewList(ListaEscenario, GL_COMPILE);
    DrawEscenario();
    glEndList();
    proceso = true;
}

//agregar Pared desde las coordenadas especificadas
void Escenario::addPared(float xIn,float xFin,float yIn,float yFin){
    //selecciono la textura

    glBindTexture (GL_TEXTURE_2D, texturaPared);
    //alto del pasillo
    float const AltoPasillo=3;
    //cantidad de unidades x la q la imagen no se deforma
    float const DimImagen=4;
    //veces q se pone la textura en el largo de la pared
    float VecesLargo;
    //veces q se pone la textura en el alto de la pared
    float VecesAlto=AltoPasillo/DimImagen;
    //mefijo si es una pared horizontal o vertical, para calcular el largo
    if (xIn==xFin){
        VecesLargo=abs((int)(yIn-yFin))/DimImagen;
    }else{
        VecesLargo=abs((int)(xIn-xFin))/DimImagen;
    }
    //comienzo el modelado
    glBegin(GL_QUADS);
      //seteo las texturas
      //y vertices
      glTexCoord2f( 0, 0 );
      glVertex3f(xIn, yIn, 0.0);
      glTexCoord2f( VecesLargo, 0 );
      glVertex3f(xFin, yFin,0.0);
      glTexCoord2f( VecesLargo, VecesAlto);
      glVertex3f(xFin, yFin, AltoPasillo);
      glTexCoord2f( 0, VecesAlto);
      glVertex3f(xIn, yIn, AltoPasillo);
    glEnd();

    //des-selecciono la textura
    glBindTexture (GL_TEXTURE_2D, 0);
}

//agrega el piso en un rectangulo, con su textura correspondiente
void Escenario::addPiso(double xIn,double xFin,double yIn,double yFin){
    //bindeo textura corespondiente
    glBindTexture (GL_TEXTURE_2D, texturaPiso);
    //cantidad de casilleros por los cuales la imagen se ve bien
    float const DimImagen=1.5;
    //calculo vecesAncho
    float VecesAncho=abs((int)(xIn-xFin))/DimImagen;
    //calculo vecesLargo
    float VecesLargo=abs((int)(yIn-yFin))/DimImagen;

    //agrego el piso
    glBegin(GL_QUADS);
      //seteo la posicion de las texturas
      //y los vertices
      glTexCoord2f( 0, 0 );
      glVertex3f(xIn, yIn, 0.0);
      glTexCoord2f( VecesAncho, 0 );
      glVertex3f(xFin, yIn, 0.0);
      glTexCoord2f( VecesAncho, VecesLargo );
      glVertex3f(xFin, yFin, 0.0);
      glTexCoord2f( 0, VecesLargo );
      glVertex3f(xIn, yFin,0.0);
    glEnd();
    //desbindeo la textura
    glBindTexture (GL_TEXTURE_2D, 0);
}


void Escenario::DrawEscenario(){
    typedef std::list<S_ptr<EstructuralUnitario> > listaEstruc;
    //obtengo los estructurales
    listaEstruc Estructurales= ModeloServidor::get_instancia()->get_mundo().get_mapa_activo()->get_estructurales();
    S_ptr<EstructuralUnitario> est;
    S_ptr<EstructuralUnitario> vecino;
    Posicion PosEst;
    float xIn;
    float xFin;
    float yIn;
    float yFin;
    //itero sobre todos los estructurales
    for (listaEstruc::iterator it=Estructurales.begin();it!=Estructurales.end();++it){
        //obtengo el estructural actual
        est=*it;
/*
             Y   |  ARRIBA
        X ->     v _____
                I |     | D
                Z |     | E
                Q |_____| R
                   ABAJO

        si un vecino EST es nulo significa q debe dibujar una pared en esa direccion, ya que no puede acceder a ese lugar

  */
        PosEst=est->get_posicion();

        xIn=-PosEst.get_x()*4;
        xFin=xIn-4;
        yIn=PosEst.get_y()*4;
        yFin=yIn+4;

        //arriba
        vecino=est->get_arriba();
        if (vecino.es_nulo()){
            addPared(xIn,xFin,yIn,yIn);
        }

        //abajo
        vecino=est->get_abajo();
        if (vecino.es_nulo()){
            addPared(xIn,xFin,yFin,yFin);
        }

        //izquierda
        vecino=est->get_izquierda();
        if (vecino.es_nulo()){
            addPared(xIn,xIn,yIn,yFin);
        }

        //derecha
        vecino=est->get_derecha();
        if (vecino.es_nulo()){
            addPared(xFin,xFin,yIn,yFin);
        }

        //agrego el piso de ese estructural
        addPiso(xIn,xFin,yIn,yFin);
    }
}
void Escenario::actualizar(Observable * observable, void * param){
	//ModeloServidor* modelo = (ModeloServidor*) observable;
	//std::cout << "cant de estruct " << modelo->get_mundo().get_mapa_activo()->get_estructurales().size() << std::endl << std::flush;
	Cargado=true;
	proceso=false;
}
