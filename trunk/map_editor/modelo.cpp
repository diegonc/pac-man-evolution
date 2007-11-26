//Header
//Incluyo las librerias necesarias
#include "modelo.h"

/* CLASE MODELO: Esta clase representa el modelo del editor de mapas. Contiene la representacion del
   mundo en memoria y permite almacenarlo en el disco en formato xml. Tambien se encarga de controlar
   que los mapas sean consistentes (no tengan mas de 1 componente conexa). */

/* Constructor: */

Modelo::Modelo(){
	this->mundo = new Mundo();
}

/* Destructor: */

Modelo::~Modelo(){
	delete(this->mundo);
}

/* Get Mundo: */

Mundo* Modelo::get_mundo(){
	return (this->mundo);
}

/* Ejecutar: */
void Modelo::ejecutar(){

}
