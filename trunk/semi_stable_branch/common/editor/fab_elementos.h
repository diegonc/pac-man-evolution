//Header
#ifndef Fab_Elementos_h_
#define Fab_Elementos_h_

//Incluyo las librerias necesarias
#include <editor/definiciones.h>
#include <common/smart_pointer.h>
#include <editor/elemento.h>
#include <editor/pas_horiz.h>
#include <editor/pas_vert.h>
#include <editor/esq_este.h>
#include <editor/esq_oeste.h>
#include <editor/esq_norte.h>
#include <editor/esq_sur.h>
#include <editor/casa_sur.h>
#include <editor/casa_este.h>
#include <editor/casa_oeste.h>
#include <editor/casa_norte.h>
#include <editor/bif_este.h>
#include <editor/bif_oeste.h>
#include <editor/bif_sur.h>
#include <editor/bif_norte.h>
#include <editor/portal_este.h>
#include <editor/portal_oeste.h>
#include <editor/portal_sur.h>
#include <editor/portal_norte.h>
#include <editor/cruce.h>
#include <editor/power_up.h>
#include <editor/bonus.h>
#include <editor/salida.h>

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
	
	/* Construir Bifur: Construye una bifurcacion segun la orientacion pasada por parametro, en las pos_x, pos_y.
	   Si pudo construir devuelve el elemento, sino devuelve NULL. */

	S_ptr<Elemento> construir_bifurc (int pos_x, int pos_y, Orientacion orientacion);
	
	/* Construir Portal: Construye un portal segun la orientacion pasada por parametro, en las pos_x, pos_y.
	   Si pudo construir devuelve el elemento, sino devuelve NULL. */

	S_ptr<Elemento> construir_portal (int pos_x, int pos_y, Orientacion orientacion);

};

#endif
