//Header
#include <editor/elemento.h>

/* CLASE ELEMENTO: Esta clase abstracta representa un elemento, ya sea estructural o modificador. El elemento
   contiene una coordenada de su vertice superior izq, un ancho y un alto, y una orientacion, y permite
   agregarse y quitarse a un mapa de un nivel determinado, realizando las validaciones pertinentes.
   Tambien contiene una orientacion. */

/* Constructor: */

Elemento::Elemento(int pos_x, int pos_y, int ancho, int alto, Orientacion orientacion){
	this->pos_x = pos_x;
	this->pos_y = pos_y;
	this->ancho = ancho;
	this->alto = alto;
	this->orientacion = orientacion;
}

/* Get Pos X: */

int Elemento::get_pos_x(){
	return this->pos_x;
}

/* Get Pos Y: */

int Elemento::get_pos_y(){
	return this->pos_y;
}

/* Get Ancho: */

int Elemento::get_ancho(){
	return this->ancho;
}

/* Get Alto: */

int Elemento::get_alto(){
	return this->alto;
}

/* Get Orientacion: */

Orientacion Elemento::get_orientacion(){
	return this->orientacion;
}

/* Contiene: */

bool Elemento::contiene (int x, int y){
	int x_rel = x - this->pos_x;
	int y_rel = y - this->pos_y;
	if ((x_rel >= 0) && (x_rel < this->get_alto()) && (y_rel >= 0) && (y_rel < this->get_ancho()))	
		return true;
	else
		return false;
}

/* Quitate: */

void Elemento::quitate(S_ptr<Elemento> instancia, Mapa* mapa){
	//Por defecto, el quitar lo unico que hace es sacar al elemento del mapa
	mapa->quitar_elemento(instancia);
}
