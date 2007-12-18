//Header
//Incluyo las librerias necesarias
#include <editor/modelo.h>

/* CLASE MODELO: Esta clase representa el modelo del editor de mapas. Contiene la representacion del
   mundo en memoria y permite almacenarlo en el disco en formato xml. Tambien se encarga de controlar
   que los mapas sean consistentes (no tengan mas de 1 componente conexa).
   Tiene una unica instancia (singleton).   */

Modelo* Modelo::instancia = NULL; //Inicializo la instancia en null

/* Constructor: */

Modelo::Modelo(){
	this->mundo = new Mundo();
}

/* Destructor: */

Modelo::~Modelo(){
	delete(this->mundo);
}

/* Get Instance: */

Modelo* Modelo::get_instance(){
	//Si no existe la instancia creo una nueva y la seteo como instancia unica
	if (Modelo::instancia == NULL)
		Modelo::instancia = new Modelo();
	return Modelo::instancia;	//Devuelvo la instancia
}

/* Get Mundo: */

Mundo* Modelo::get_mundo(){
	return (this->mundo);
}

/* Set Mundo: */

void Modelo::set_mundo(Mundo* nuevo_mundo){
	//Si el modelo tenia un mundo lo elimino
	if (this->mundo != NULL)
		delete(this->mundo);
	//Asigno el nuevo mundo al modelo y aviso a los observadores que el mundo cambio
	this->mundo = nuevo_mundo;
	this->set_cambio();
	this->avisar_observadores(NULL);	
}

/* Destroy: */

void Modelo::destroy(){
	delete(instancia);
}
