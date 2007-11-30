//Header
#ifndef Traductor_h_
#define Traductor_h_

#include "definiciones.h"
#include "../common/smart_pointer.h"

/* CLASE TRADUCTOR: Clase que se encarga de traducir un mundo de alto nivel (del editor),
   a un mundo de bajo nivel (para el servidor). */

class Traductor {

	public:

	/* Traducir: Devuelve un nuevo mundo de bajo nivel, generado a partir del mundo de alto
	   nivel pasado por parametro. */
	MundoBajoNivel* traducir(Mundo* mundo);
	
	private:
	
	/* Trad Cod Elemento: Traduce un codigo de elemento de alto nivel a un codigo de elemento de 
	   bajo nivel. */
	const char trad_cod_elemento(TipoElem tipo);
	
};

#endif
