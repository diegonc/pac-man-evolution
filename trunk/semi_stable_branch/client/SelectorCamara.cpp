#include "SelectorCamara.h"

SelectorCamara::SelectorCamara(){
	NroCam=0;
}

void SelectorCamara::siguiente(){
	NroCam=(NroCam+1)%Cantidad;
}

void SelectorCamara::ejecutar(){
	static GLfloat pos[4] = {0, 0, 1, 0 };
	switch (NroCam){
		case CAMARANEAR:
			glRotatef(-75, 1, 0.0, 0.0);
			//agrego la luz (estaba habilitada (INITGL)) es una luz del tipo posicion con la pos antes mencionada
			glLightfv( GL_LIGHT0, GL_POSITION, pos );
			glTranslatef(0.0,9 , -5);
			break;
		case CAMARAFAR:
			glRotatef(-65, 1, 0.0, 0.0);
			//agrego la luz (estaba habilitada (INITGL)) es una luz del tipo posicion con la pos antes mencionada
			glLightfv( GL_LIGHT0, GL_POSITION, pos );
			glTranslatef(0.0,15 , -10);
			break;
		case CAMARAUPPER:
			static GLfloat pos[4] = {0, 0, 1, 0 };
			//agrego la luz (estaba habilitada (INITGL)) es una luz del tipo posicion con la pos antes mencionada
			glLightfv( GL_LIGHT0, GL_POSITION, pos );
			glTranslatef(0,0 , -40);
			break;
		default:
			break;
	}

}
