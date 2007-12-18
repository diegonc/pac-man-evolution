//Header
#include <editor/punto.h>

/* CLASE PUNTO: Clase que representa un punto en un espacio de R2. Tiene coordenadas (x,y). */

/* Constructor: */

Punto::Punto(int x, int y){
	this->x = x;
	this->y = y;
}

/* Get X: */

int Punto::get_x(){
	return this->x;
}

/* Get Y: */

int Punto::get_y(){
	return this->y;
}
