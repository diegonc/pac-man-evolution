//Header
#ifndef Fab_Elementos_h_
#define Fab_Elementos_h_

//Incluyo las librerias necesarias
#include "definiciones.h"
#include "../common/smart_pointer.h"
#include "elemento.h"

using namespace std;

class Elemento;

/* CLASE FABRICA ELEMENTOS: Clase que se encarga de encapsular la creacion de elementos de cualquier tipo (modificadores
o estructurales). */

class Fab_Elementos {

	public:

	//Destructor virtual
	virtual ~Fab_Elementos(){}

	/* Construir: Construye un elemento segun el tipo mandado como parametro, con las posiciones pos_x, pos_y y la
	   orientacion mandada por parametro. 
	   Si lo puedo construir devuelve el elemento, sino devuelve NULL. */

	virtual S_ptr<Elemento> construir (TipoElem tipo, int pos_x, int pos_y, Orientacion orientacion);

};

#endif
