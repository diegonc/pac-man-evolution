#include "MiniMapa.h"


MiniMapa::MiniMapa(){
	//CargarTexturas();
}	

MiniMapa::~MiniMapa(){
	SDL_FreeSurface(Mapa);
	SDL_FreeSurface(Casillero);	
	SDL_FreeSurface(Pacman);
	SDL_FreeSurface(Fantasma);
	SDL_FreeSurface(PowerUP);
	SDL_FreeSurface(Frutita);
	SDL_FreeSurface(Quesito);
}	

void MiniMapa::ejecutar(SDL_Surface* Screen){
	Jugador* JugMio=ModeloServidor::get_instancia()->get_jugador(JugadorLocal::get_instancia()->get_id());
	if (JugMio!=NULL){
		Dibujar(JugMio,Screen);		
	}
}

void MiniMapa::DibujarCasillero(SDL_Surface* Screen,int ImgXCurr,int ImgYCurr){
	SDL_Rect RectCasillero={0,0,0,0};
	//seteo el tamanio y la posicion del minimapa sobre la pantalla
	RectCasillero.x=(Sint16)ImgXCurr;
	RectCasillero.y=(Sint16)ImgYCurr;
	RectCasillero.w=DimCasillero;
	RectCasillero.h=DimCasillero;

	SDL_FillRect(Screen, &RectCasillero, SDL_MapRGBA(Screen->format,0,0,0,0));
	
	/*SDL_SetColorKey(Casillero, SDL_SRCCOLORKEY, 
	  SDL_MapRGB(Casillero->format, 0, 0, 255));
	*///escribo el Casillero en la pantalla				
	SDL_BlitSurface(Casillero, NULL, Screen, &RectCasillero);
//	SDL_UpdateRects(Screen, 1, &RectCasillero);
	//S_ptr<EstructuralUnitario> Est=ModeloServidor::get_instancia()->get_mundo().get_mapa_activo().get_estructural(P)
	//DibujarConexionesEstructural(Est,ImgXCurr,ImgYCurr,Screen);
}

void MiniMapa::DibujarJugador(SDL_Surface* Screen, Jugador* jug, int ImgXCurr, int ImgYCurr){
	SDL_Surface* TextJugad;
	if (jug->get_personaje()->get_tipo()==Personaje::fantasma){
		TextJugad=Fantasma;
	}else{
		TextJugad=Pacman;				
	}
	DibujarObjeto(Screen,TextJugad,ImgXCurr,ImgYCurr);
}

void MiniMapa::DibujarComestible(SDL_Surface* Screen, S_ptr<Comestible> Comest, int ImgXCurr, int ImgYCurr){
	SDL_Surface* TextComest;
	if (Comest->get_tipo()==Comestible::frutita){
		TextComest=Frutita;
	}else if (Comest->get_tipo()==Comestible::power_up){
		TextComest=PowerUP;
	}else{
		TextComest=Quesito;
	}
	DibujarObjeto(Screen,TextComest,ImgXCurr,ImgYCurr);
}

void MiniMapa::DibujarObjeto(SDL_Surface* Screen, SDL_Surface* TextObj, int ImgXCurr, int ImgYCurr){
	SDL_Rect RectObjeto={0,0,0,0};
	//seteo el tamanio y la posicion del minimapa sobre la pantalla
	RectObjeto.x=(Sint16)ImgXCurr;
	RectObjeto.y=(Sint16)ImgYCurr;
	RectObjeto.w=DimObjeto;
	RectObjeto.h=DimObjeto;

/*	SDL_SetColorKey(TextObj, SDL_SRCCOLORKEY, 
	  SDL_MapRGB(TextObj->format, 0, 0, 255));
*/	//escribo el Casillero en la pantalla				
	SDL_BlitSurface(TextObj, NULL, Screen, &RectObjeto);					
}

void MiniMapa::Dibujar(Jugador* jug, SDL_Surface* Screen){
	SDL_Rect RectMapa={0,0,0,0};
	int ImgXCurr;
	int ImgYCurr;		
	int XCurr;
	int YCurr;		

	std::list<Jugador*> jugadores = ModeloServidor::get_instancia()->get_jugadores();
	std::list< S_ptr<Comestible> > comestibles=ModeloServidor::get_instancia()->get_mundo().get_mapa_activo()->get_comestibles();

	Posicion& Centro=jug->get_posicion();
	Posicion CentroFloor;
	CentroFloor.set_x(floor(Centro.get_x()));
	CentroFloor.set_y(floor(Centro.get_y()));

	//obtengo el estructural q va a ir en la esquina superior izq del minimapa
	Posicion PosSupIzq;
	PosSupIzq.set_x(CentroFloor.get_x()-4);
	PosSupIzq.set_y(CentroFloor.get_y()-4);

	//posicion q uso para pivotear sobre los estructurales
	Posicion PosPivot;

	//seteo el tamanio y la posicion del minimapa sobre la pantalla
	RectMapa.x=(Sint16)InitXMiniMapa;
	RectMapa.y=(Sint16)InitYMiniMapa;
	RectMapa.w=DimMiniMapa;
	RectMapa.h=DimMiniMapa;

	//seteo el canal alfa
	SDL_FillRect(Screen, &RectMapa, SDL_MapRGBA(Screen->format,0,0,0,0));

	SDL_SetColorKey(Mapa, SDL_SRCCOLORKEY, 
	  SDL_MapRGB(Mapa->format, 0, 0, 255));

	//dibujo el mapa
	SDL_BlitSurface(Mapa, NULL, Screen, &RectMapa);	

	for(int i=0;i< (DimensionTablero * DimensionTablero);++i){
		//obtengo la col del MiniMapa
		XCurr=(i%DimensionTablero);
		//obtengo la fila del MiniMapa
		YCurr=(int)floor(i/DimensionTablero);
		//obtengo la posicion en estructurales sobre la q voy a dibujar
		PosPivot.set_x(PosSupIzq.get_x()+XCurr);
		PosPivot.set_y(PosSupIzq.get_y()+YCurr);
		//seteo la posicion de la imagen
		//inicial del Mapa + Marco + (Fila o Col) * dimension del casillero
		ImgXCurr=InitXMiniMapa + Marco + (XCurr*DimCasillero);
		ImgYCurr=InitYMiniMapa + Marco + (YCurr*DimCasillero);
		//valida si la posicion es valida (podria no serlo) y de ser asi si hay estructural
		if (hayEstructural(PosPivot)){
			//begin dibujo casillero
			DibujarCasillero(Screen,ImgXCurr,ImgYCurr);			
			//end dibujo casillero
		}

		for (std::list< S_ptr<Comestible> >::iterator it=comestibles.begin();it!=comestibles.end();++it){
			S_ptr<Comestible> comest=*it;
			Posicion Pos=comest->get_posicion();
			if ((PosPivot.get_x()==floor(Pos.get_x())) && (PosPivot.get_y()==floor(Pos.get_y()))) {
				DibujarComestible(Screen,comest,ImgXCurr+4,ImgYCurr+4);				
			}

		}		

		for (std::list<Jugador*>::iterator it=jugadores.begin();it!=jugadores.end();++it){
			Jugador * jugad=*it;
			Posicion Pos=jugad->get_posicion();
			if ((PosPivot.get_x()==floor(Pos.get_x())) && (PosPivot.get_y()==floor(Pos.get_y()))) {
				DibujarJugador(Screen,jugad,ImgXCurr+4,ImgYCurr+4);
			}				

		}
	}		
		
	SDL_UpdateRects(Screen, 1, &RectMapa);

}

bool MiniMapa::hayEstructural(Posicion& P){
	S_ptr<MapaBajoNivel> mapa=ModeloServidor::get_instancia()->get_mundo().get_mapa_activo();
	//si la posicion en X es invalida
	if ((P.get_x()<0) || (P.get_x()>=mapa->get_ancho())){
		return false;
	//si la posicion en Y es invalida
	}else if ((P.get_y()<0) || (P.get_y()>=mapa->get_alto())){
		return false;
	//si la posicion es valida
	}else{
		S_ptr<EstructuralUnitario> estruc=mapa->get_estructural(P);
		if (!estruc.es_nulo()){
			return true;
		}else{
			return false;
		}
	}

}

void MiniMapa::CargarTexturas(){
	CargarSDLSurface(&Mapa,"./MiniMapa/Mapa.bmp");
	CargarSDLSurface(&Casillero,"./MiniMapa/Casillero.bmp");
	CargarSDLSurface(&Pacman,"./MiniMapa/Pacman.bmp");
	CargarSDLSurface(&Fantasma,"./MiniMapa/Fantasma.bmp");
	CargarSDLSurface(&PowerUP,"./MiniMapa/Powerup.bmp");
	CargarSDLSurface(&Frutita,"./MiniMapa/Frutita.bmp");
	CargarSDLSurface(&Quesito,"./MiniMapa/Quesito.bmp");
}

void MiniMapa::CargarSDLSurface(SDL_Surface** Textura,char* Nombre){
	//cargo la textura del archivo
	*Textura = SDL_LoadBMP(Nombre);		
	//seteo el color transparente, se utilizo el azul
	SDL_SetColorKey(*Textura, SDL_SRCCOLORKEY,SDL_MapRGB((*Textura)->format, 0, 0, 255));
}

