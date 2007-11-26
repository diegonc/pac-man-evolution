//Header
#ifndef Pasillo_h_
#define Pasillo_h_

//Incluyo las librerias necesarias
#include "pasillo.h"

/* CLASE PASILLO: Clase concreta que hereda de estructural, y representa a un pasillo con dos posibles orientaciones
   (ESTE U OESTE --> HORIZONTAL, NORTE O SUR --> VERTICAL) */

class Pasillo {

	/* Constructor: Inicializa el elemento con los datos pasados por parametro. */
	Pasillo(int pos_x, int pos_y, Orientacion orientacion);

	/* Destructor: Libera los recursos consumidos por el elemento. */
	virtual ~Elemento(){}

	/* Get Pos X: Devuelve la posicion x del elemento. */
	int get_pos_x();

	/* Get Pos Y: Devuelve la posicion y del elemento. */
	int get_pos_y();
	
	/* Get Ancho: Devuelve el ancho en unidades del elemento. */
	int get_ancho();
	
	/* Get Alto: Devuelve el alto en unidades del elemento. */
	int get_alto();

	/* Get Orientacion: Devuelve la orientacion del elemento */
	Orientacion get_orientacion();
	
	/* Es Punto Conexion: Dadas unas coordenadas x,y devuelve true si las mismas son un punto de conexion del
	  elemento o false en caso contrario */
	virtual bool es_punto_conexion(int x, int y) = 0;

	/* Es Habitable: Dadas unas coordenadas x,y devuelve true si las mismas son habitables por un personaje o
	   modificador y false en caso contrario */
	virtual bool es_habitable(int x, int y) = 0;

	/* Agregate: Dado el mapa pasado por parametro, el elemento verifica si puede insertarse en mismo,en 
	   la posicion con la que fue creado. Si puede, se agrega y se conecta con todos los vecinos (si es estruct).
	   Devuelve true si se pudo agregar, false en caso contrario. */
	virtual bool agregate(Mapa* mapa) = 0;

	/* Quitate: Dado el mapa pasado por parametro, el elemento se encarga de removerse del mismo. */
	virtual void quitate(Mapa* mapa);

	/* Es Estructural: Devuelve true si el elemento es estructural, false en caso contrario */
	virtual bool es_estructural() = 0;

	//operadores de comparacion

	friend bool operator==(Elemento &elem1, Elemento &elem2){
		if ((elem1.get_pos_x() == elem2.get_pos_x()) && (elem1.get_pos_y() == elem2.get_pos_y()))
			return true;
		else
			return false;
	}

	friend bool operator!=(Elemento &elem1, Elemento &elem2){
		if ((elem1.get_pos_x() != elem2.get_pos_x()) || (elem1.get_pos_y() != elem2.get_pos_y()))
			return true;
		else
			return false;
	}

	friend bool operator<(Elemento &elem1, Elemento &elem2){
		if (elem1.get_pos_x() < elem2.get_pos_x())
			return true;
		else
			if ((elem1.get_pos_x() == elem2.get_pos_x()) && (elem1.get_pos_y() < elem2.get_pos_y()))
				return true;
			else
				return false;
	}
	
};

#endif
