//Header
#ifndef Fab_Elementos_h_
#define Fab_Elementos_h_

//Incluyo las librerias necesarias
#include "definiciones.h"
#include "../common/smart_pointer.h"
#include "elemento.h"
#include "pas_horiz.h"
#include "pas_vert.h"
#include "esq_este.h"
#include "esq_oeste.h"
#include "esq_norte.h"
#include "esq_sur.h"
#include "casa_sur.h"
#include "power_up.h"
#include "bonus.h"
#include "salida.h"

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
	   Si lo pudo construir devuelve el elemento, sino devuelve NULL. */

	virtual S_ptr<Elemento> construir (TipoElem tipo, int pos_x, int pos_y, Orientacion orientacion);

	private:

	/* Construir Pasillo: Construye un pasillo segun la orientacion pasada por parametro, en las pos_x, pos_y.
	   Si lo pudo construir devuelve el elemento, sino devuelve NULL. */

	S_ptr<Elemento> construir_pasillo (int pos_x, int pos_y, Orientacion orientacion);

	/* Construir Esquina: Construye una esquina segun la orientacion pasada por parametro, en las pos_x, pos_y.
	   Si pudo construir devuelve el elemento, sino devuelve NULL. */

	S_ptr<Elemento> construir_esquina (int pos_x, int pos_y, Orientacion orientacion);
	
	/* Construir Casa: Construye una casa de fantasmas segun la orientacion pasada por parametro, en las pos_x, pos_y.
	   Si pudo construir devuelve el elemento, sino devuelve NULL. */

	S_ptr<Elemento> construir_casa (int pos_x, int pos_y, Orientacion orientacion);

};

#endif
