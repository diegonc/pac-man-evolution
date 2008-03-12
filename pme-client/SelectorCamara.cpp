#include "SelectorCamara.h"

SelectorCamara::SelectorCamara(){
	NroCam=0;
}

void SelectorCamara::siguiente(){
	NroCam=(NroCam+1)%Cantidad;
}

void SelectorCamara::ejecutar(){
	switch (NroCam){
		case CAMARANEAR:
			glRotatef(-75, 1, 0.0, 0.0);
			glTranslatef(0.0,9 , -5);
			break;
		case CAMARAFAR:
			glRotatef(-65, 1, 0.0, 0.0);
			glTranslatef(0.0,15 , -10);
			break;
		case CAMARAUPPER:
			glTranslatef(0,0 , -40);
			break;
		default:
			break;
	}

}
