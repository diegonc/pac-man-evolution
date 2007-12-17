//Header
#include <editor/dato_vertice.h>

/* CLASE DATO VERTICE: Clase que representa el contenido de un vertice para el grafo que controla
   las conexiones de elementos. */

/* Constructor: */

DatoVertice::DatoVertice(S_ptr<Elemento> elem){
	this->elem = elem;
}

/* Get Elemento:  */

S_ptr<Elemento> DatoVertice::get_elemento(){
	return this->elem;
}

/* Marcar: */

void DatoVertice::marcar(){
	this->marcado = true;
}

/* Desmarcar: */

void DatoVertice::desmarcar(){
	this->marcado = false;
}

/* Esta Marcado: */

bool DatoVertice::esta_marcado(){
	return this->marcado;
}
