//HEADER

#ifndef ITEM_ELEM_H_
#define ITEM_ELEM_H_

#include <editor/definiciones.h>

/* CLASE ITEM ELEM: Clase que simboliza un item para un panel de elementos. Contiene
   un tipo, una orientacion y una ruta para su imagen. */

class ItemElem {

  private:
	  TipoElem tipo; //Tipo del elemento
	  Orientacion orientacion; //Orientacion del elemento
  	  char* ruta; //Ruta del elemento

  public:

	//Constructor: Inicializa al item con los datos pasados por parametro
	ItemElem(TipoElem tipo, Orientacion orientacion, char* ruta_imagen);

	//Get Tipo: Devuelve el tipo del elemento
  	TipoElem get_tipo() const;
  
  	//Get Orientacion: Devuelve la orientacion del elemento
  	Orientacion get_orientacion() const;
  
  	//Get Ruta Imagen: Devuelve la ruta de la imagen del elemento
  	char* get_ruta_imagen() const;

};

#endif
