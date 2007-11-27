//Header
#ifndef Modificador_h_
#define Modificador_h_

//Incluyo las librerias necesarias
#include "elemento.h"

/* CLASE MODIFICADOR: Esta clase abstracta representa un elemento modificador y desciende de elemento.
   Todos los modificadores tienen un tamanio de 1 x 1 y su orientacion es nula. */

class Modificador : public Elemento {

	protected:

	/* Constructor: Inicializa el elemento con los datos pasados por parametro. El tamanio es de 1 x 1.
	   La orientacion es nula. */
	Modificador(int pos_x, int pos_y);

	public:

	/* Destructor: Libera los recursos consumidos por el elemento. */
	virtual ~Modificador(){}

	/* Es Estructural: Devuelve false porque el elemento no es estructural. */
	virtual bool es_estructural();

	/* Es Punto Conexion: Devuelve false, puesto que los modificadores no tienen puntos de conexion. */
	virtual bool es_punto_conexion(int x, int y);

	/* Es Habitable: Devuelve false, puesto que los modificadores no son habitables. */
	virtual bool es_habitable(int x, int y);

	/* Agregate: Dado el mapa pasado por parametro, el modificador verifica si puede insertarse en la posicion con
	   la que fue creado. Si no hay otro modificador en esa pos y ademas el lugar
	   es habitable, se agrega y devuelve true. Sino no se agrega y devuelve false. */
	virtual bool agregate(S_ptr<Elemento> instancia, Mapa* mapa);
	
};

#endif
