//Header
#ifndef Esq_Este_h_
#define Esq_Este_h_

//Incluyo las librerias necesarias
#include <editor/estructural.h>
#include <editor/punto.h>

/* CLASE ESQUINA ESTE: Clase que representa una esquina que conecta el ESTE con el SUR. Su orientacion es ESTE. Hereda de estructural. */

class EsqEste : public Estructural {

	public:

	/* Constructor: Inicializa una esquina este con las posiciones pasadas por parametros. */
	EsqEste (int pos_x, int pos_y);
	
	/* Get Tipo: Devuelve el tipo del elemento */
	virtual TipoElem get_tipo();
	
	/* Get Ruta Imagen: Devuelve una cadena con la ruta donde se encuentra la imagen que representa al elemento */
	virtual char* get_ruta_imagen();

};

#endif
