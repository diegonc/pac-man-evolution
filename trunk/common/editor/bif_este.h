//Header
#ifndef Bif_Este_h_
#define Bif_Este_h_

//Incluyo las librerias necesarias
#include <editor/estructural.h>
#include <editor/punto.h>

/* CLASE BIF ESTE: Clase que representa una bifurcacion con orientacion ESTE. Hereda de Estructural. */

class BifEste : public Estructural {

	public:

	/* Constructor: Inicializa una bifurcacion este con las posiciones pasadas por parametros. */
	BifEste (int pos_x, int pos_y);

	/* Get Ruta Imagen: Devuelve una cadena con la ruta donde se encuentra la imagen que representa al elemento */
	virtual char* get_ruta_imagen();
	
	/* Get Tipo: Devuelve el tipo del elemento */
	virtual TipoElem get_tipo();

};

#endif
