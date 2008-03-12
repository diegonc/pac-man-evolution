//Header
#ifndef Salida_h_
#define Salida_h_

//Incluyo las librerias necesarias
#include <editor/modificador.h>

/* CLASE SALIDA: Clase que representa la salida del PacMan. Desciende de modificador. Ocupa un casillero. */

class Salida : public Modificador {

	public:

	/* Constructor: Inicializa la salida en una posicion determinada. */
	Salida (int pos_x, int pos_y);
	
	/* Get Tipo: Devuelve el tipo del elemento */
	virtual TipoElem get_tipo();
	
	/* Get Ruta Imagen: Devuelve una cadena con la ruta donde se encuentra la imagen que representa al elemento */
	virtual char* get_ruta_imagen();
	
	/* Agregate: Dado el mapa pasado por parametro, el modificador verifica si puede insertarse en la posicion con
       la que fue creado. Si no hay otro modificador en esa pos y ademas el lugar
       es habitable, se agrega y devuelve true. Sino no se agrega y devuelve false. 
	   En este caso tmb se valida que haya una sola salida de pacman. */
	virtual bool agregate(S_ptr<Elemento> instancia, Mapa* mapa);
	
	/* Quitate: Dado el mapa pasado por parametro, el elemento se encarga de removerse del mismo. */
	virtual void quitate(S_ptr<Elemento> instancia, Mapa* mapa);

};

#endif
