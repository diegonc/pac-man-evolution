//Header
#ifndef Modelo_h_
#define Modelo_h_

//Incluyo las librerias necesarias
#include "mundo.h"

using namespace std;

/* CLASE MODELO: Esta clase representa el modelo del editor de mapas. Contiene la representacion del
   mundo en memoria y permite almacenarlo en el disco en formato xml. Tambien se encarga de controlar
   que los mapas sean consistentes (no tengan mas de 1 componente conexa). */

class Modelo {

	//Atributos
	private:
		Mundo* mundo; //Referencia al mundo contenido en el modelo

	public:

	/* Constructor: Inicializa el modelo, crea un nuevo mundo vacio. */
	Modelo();

	/* Destructor: Libera los recursos consumidos por el modelo. */
	~Modelo();

	/* Get Mundo: Devuelve una referencia al mundo contenido en el modelo */
	Mundo* get_mundo();

	/* Ejecutar: Se encarga de ejecutar el modelo. El mismo revisa periodicamente si algun mapa
	   cambia, y si esto sucede se encarga de controlar que el mapa que se actualizo tenga una
	   sola componente conexa. */
	void ejecutar();

};

#endif
