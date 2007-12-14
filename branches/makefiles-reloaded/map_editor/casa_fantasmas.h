//Header
#ifndef Casa_fantasmas_h
#define Casa_fantasmas_h

//Incluyo las librerias necesarias
#include "definiciones.h"
#include "estructural.h"
#include "punto.h"

/* CLASE CASA FANTASMA: Clase que representa una casa de fantasmas en una orientacion determinada. Hereda de estructural. */

class CasaFantasmas : public Estructural {

	public:

	/* Constructor: Inicializa una casa de fantasmas con una orientacion y posicion determinada. */
	CasaFantasmas (int pos_x, int pos_y, Orientacion orientacion);
	
	/* Agregate: Dado el mapa pasado por parametro, el elemento verifica si puede insertarse en mismo,en 
	   la posicion con la que fue creado. Si puede, se agrega y se conecta con todos los vecinos.
	   Devuelve true si se pudo agregar, false en caso contrario.
	   En este caso tambien se valida que haya una unica casa de fantasmas en el mapa.	*/
	virtual bool agregate(S_ptr<Elemento> instancia, Mapa* mapa);
	
	/* Quitate: Dado el mapa pasado por parametro, el elemento se encarga de removerse del mismo. */
	virtual void quitate(S_ptr<Elemento> instancia, Mapa* mapa);
	
	/* Get Tipo: Devuelve el tipo del elemento */
	virtual TipoElem get_tipo();

};

#endif
