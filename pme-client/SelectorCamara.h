#ifndef SELECTORCAMARA_H
#define SELECTORCAMARA_H

#include <GL/gl.h>
#include <GL/glu.h>


#define Cantidad 	3
#define CAMARANEAR 	0
#define CAMARAFAR 	1
#define CAMARAUPPER 	2


class SelectorCamara{
	int NroCam;
	public:
	SelectorCamara();
	
	void siguiente();

	void ejecutar();
};

#endif
