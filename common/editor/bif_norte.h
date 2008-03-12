//Header
#ifndef Bif_Norte_h_
#define Bif_Norte_h_

//Incluyo las librerias necesarias
#include <editor/estructural.h>
#include <editor/punto.h>

/* CLASE BIF NORTE: Clase que representa una bifurcacion con orientacion NORTE. Hereda de Estructural. */

class BifNorte : public Estructural {

	public:

	/* Constructor: Inicializa una bifurcacion con las posiciones pasadas por parametros. */
	BifNorte (int pos_x, int pos_y);

	/* Get Ruta Imagen: Devuelve una cadena con la ruta donde se encuentra la imagen que representa al elemento */
	virtual char* get_ruta_imagen();
		
	/* Get Tipo: Devuelve el tipo del elemento */
	virtual TipoElem get_tipo();

};

#endif
