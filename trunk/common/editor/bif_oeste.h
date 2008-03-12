//Header
#ifndef Bif_Oeste_h_
#define Bif_Oeste_h_

//Incluyo las librerias necesarias
#include <editor/estructural.h>
#include <editor/punto.h>

/* CLASE BIF OESTE: Clase que representa una bifurcacion con orientacion OESTE. Hereda de Estructural. */

class BifOeste : public Estructural {

	public:

	/* Constructor: Inicializa una bifurcacion este con las posiciones pasadas por parametros. */
	BifOeste (int pos_x, int pos_y);

	/* Get Ruta Imagen: Devuelve una cadena con la ruta donde se encuentra la imagen que representa al elemento */
	virtual char* get_ruta_imagen();
		
	/* Get Tipo: Devuelve el tipo del elemento */
	virtual TipoElem get_tipo();


};

#endif
