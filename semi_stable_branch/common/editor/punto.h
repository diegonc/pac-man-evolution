//Header
#ifndef Punto_h_
#define Punto_h_

/* CLASE PUNTO: Clase que representa un punto en un espacio de R2. Tiene coordenadas (x,y). */

class Punto {

	private:

	  int x; //Coord x
	  int y; //Coord y

	public:

	  /* Constructor: Inicializa el punto con las coords pasadas por parametro */
	  Punto(int x, int y);

	  /* Get X: Devuelve la coord x del punto */
	  int get_x();

	  /* Get Y: Devuelve la coord y del punto */
	  int get_y();
	
};

#endif
