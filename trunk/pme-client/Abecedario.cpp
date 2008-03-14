#include "Abecedario.h"


Abecedario::Abecedario(bool arriba,unsigned int Unid){
	this->arriba=arriba;
	this->Unidades=Unid;
}

Abecedario::~Abecedario(){
	SDL_FreeSurface(TextABC);
	SDL_FreeSurface(TextLetra);
}

void Abecedario::DibujarLetra(SDL_Surface* Screen, int ImgXCurr, int ImgYCurr){
	SDL_Rect RectObjeto={0,0,0,0};
	//seteo el tamanio y la posicion del minimapa sobre la pantalla
	RectObjeto.x=(Sint16)ImgXCurr;
	RectObjeto.y=(Sint16)ImgYCurr;
	RectObjeto.w=DimLetra;
	RectObjeto.h=DimLetra;

/*	SDL_SetColorKey(TextLetra, SDL_SRCCOLORKEY, 
	  SDL_MapRGB(TextLetra->format, 0, 0, 255));*/
	//escribo el Casillero en la pantalla				
	SDL_BlitSurface(TextLetra, NULL, Screen, &RectObjeto);					
	SDL_UpdateRects(Screen, 1, &RectObjeto);
}
void Abecedario::ImprimirFrase(SDL_Surface* Screen,std::string Frase){
	SDL_Rect RectABC={0,0,0,0};
	int LongCadena=Frase.length();
	int LongXImg=LongCadena*DimLetra;
	int InitImgX=0;//(ScreenWidth-LongXImg)/2;
	int InitImgY;
	if (arriba)
		InitImgY=Unidades*DimLetra;
	else
		InitImgY=ScreenHeight-DimLetra - (Unidades*DimLetra);	
	int ImgXCurr=InitImgX;
	int ImgYCurr=InitImgY;


	
	//seteo el tamanio y la posicion del minimapa sobre la pantalla
	RectABC.x=(Sint16)InitImgX;
	RectABC.y=(Sint16)InitImgY;
	RectABC.w=LongCadena;
	RectABC.h=DimLetra;

	//SDL_UpdateRects(Screen, 1, &RectABC);

	//seteo el canal alfa
	SDL_FillRect(Screen, &RectABC, SDL_MapRGBA(Screen->format,0,0,0,0));



	for (int i=0;i<LongCadena;++i){		
		get_letra(Frase[i]);
		DibujarLetra(Screen,ImgXCurr,ImgYCurr);
		ImgXCurr+=DimLetra;
		//std::cout << "IMGXCURR:" << ImgXCurr << std::endl;
		SDL_UpdateRects(Screen, 1, &RectABC);
	}

		
	
}

//#include <iostream>
void Abecedario::get_letra(char letra){
	int key=(int)letra;	
	int fila=(int) (key/LetrasXFC);
	int col=key % LetrasXFC;
	fila-=2;

	//std::cout << "Fila :"<< fila << "\n Col :" << col << std::endl;
	

	int XLetra=col*DimLetra;
	int YLetra=fila*DimLetra;

	SDL_Rect RectLetra={0,0,0,0};
	
	//seteo el tamanio y la posicion del minimapa sobre la pantalla
	RectLetra.x=(Sint16)XLetra;
	RectLetra.y=(Sint16)YLetra;
	RectLetra.w=DimLetra;
	RectLetra.h=DimLetra;
	
	SDL_Rect RectDest={0,0,0,0};
	
	//seteo el tamanio y la posicion del minimapa sobre la pantalla
	RectDest.x=0;
	RectDest.y=0;
	RectDest.w=DimLetra;
	RectDest.h=DimLetra;

//	SDL_FillRect(TextLetra, &RectDest , SDL_MapRGBA(TextLetra->format,1,1,1,1));

	SDL_BlitSurface(TextABC, &RectLetra, TextLetra, NULL);//&RectDest);
}

void Abecedario::CargarTextura(){
	CargarSDLSurface(&TextABC,APP_DATA_DIR_S "./ABC.bmp");
	CargarSDLSurface(&TextLetra,APP_DATA_DIR_S "./Letra.bmp");
}

void Abecedario::CargarSDLSurface(SDL_Surface** Textura,char* Nombre){
	//cargo la textura del archivo
	*Textura = SDL_LoadBMP(Nombre);		
	//seteo el color transparente, se utilizo el azul
//	SDL_SetColorKey(*Textura, SDL_SRCCOLORKEY,SDL_MapRGB((*Textura)->format, 0, 0, 255));
}

