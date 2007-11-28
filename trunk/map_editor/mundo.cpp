//Header
#include "mundo.h"

/* CLASE MUNDO: Esta clase representa el mundo, compuesto por niveles. El mismo permite insertar o quitar nuevos
   niveles, reordenarlos, e insertar o quitar elementos estructurales y modificadores en un mapa determinado. */

/* Constructor: */

Mundo::Mundo(){}

/* Destructor: */

Mundo::~Mundo(){
	this->niveles.clear();
}

/* Agregar Nivel: */

int Mundo::agregar_nivel(int tam_X, int tam_Y){
	S_ptr<Nivel> nivel (new Nivel(tam_X, tam_Y));
	this->niveles.push_back(nivel);
	return this->niveles.size();
}

/* Quitar Nivel: */

void Mundo::quitar_nivel(unsigned int nOrden){
	if ((nOrden > 0) && (nOrden <= this->niveles.size())) {
		unsigned int cont = 1;
		list<S_ptr<Nivel> >::iterator it = this->niveles.begin();
		while (cont < nOrden){
			it++;
			cont++;
		}
		this->niveles.erase(it); 
	}
}

/* Agregar Elemento: */

bool Mundo::agregar_elemento(TipoElem tipo, unsigned int nOrden, int posX, int posY, Orientacion orientacion){
	bool result = true;
	if ((nOrden > 0) && (nOrden <= this->niveles.size())){
		unsigned int cont = 1;
		list<S_ptr<Nivel> >::iterator it = this->niveles.begin();
		while (cont < nOrden){
			it++;
			cont++;
		}
		S_ptr<Nivel> nivel = *it;
		result = nivel->agregar_elemento(tipo, posX, posY, orientacion);
	} else
		result = false;
	return result;
}

/* Quitar Elemento: */

bool Mundo::quitar_elemento(unsigned int nOrden, int posX, int posY){
	bool result = true;
	if ((nOrden > 0) && (nOrden <= this->niveles.size())){
		unsigned int cont = 1;
		list<S_ptr<Nivel> >::iterator it = this->niveles.begin();
		while (cont < nOrden){
			it++;
			cont++;
		}
		S_ptr<Nivel> nivel = *it;
		result = nivel->quitar_elemento(posX, posY);
	} else
		result = false;
	return result;
}

/* Get Nivel: */

S_ptr<Nivel> Mundo::get_nivel(unsigned int nOrden){
	S_ptr<Nivel> nivel;
	if ((nOrden > 0) && (nOrden <= this->niveles.size())){
		unsigned int cont = 1;
		list<S_ptr<Nivel> >::iterator it = this->niveles.begin();
		while (cont < nOrden){
			it++;
			cont++;
		}
		nivel = *it;
	}
	return nivel;
}

/* Promover: */

void Mundo::promover(unsigned int nOrden){

}

/* Degradar: */

void Mundo::degradar(unsigned int nOrden){

}

/* ////////////////////TEMPORAL///////////////////////// */

void Mundo::imprimir_nivel(unsigned int nOrden){
	if ((nOrden > 0) && (nOrden <= this->niveles.size())){
		unsigned int cont = 1;
		list<S_ptr<Nivel> >::iterator it = this->niveles.begin();
		while (cont < nOrden){
			it++;
			cont++;
		}
		S_ptr<Nivel> nivel = *it;
		nivel->imprimir_mapa();
	}
}
