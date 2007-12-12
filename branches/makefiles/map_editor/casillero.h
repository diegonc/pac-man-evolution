//Header
#ifndef Casillero_h_
#define Casillero_h_

//Incluyo las librerias necesarias
#include "elemento.h"
#include "../common/smart_pointer.h"

using namespace std;

class Elemento;

/* CLASE CASILLERO: Esta clase representa un casillero, que es la unidad espacial minima en el mapa. Cada casillero
   puede contener una parte de un elemento estructural y ademas un modificador. El casillero ademas tiene una 
   posicion x y una posicion y. */

class Casillero {
   //Atributos:
   private:
	int pos_x;
	int pos_y;
	S_ptr<Elemento> estructural;
	S_ptr<Elemento> modificador;

   public:

	/* Constructor: Inicializa el casillero con la pos pasada por parametro y vacio (sin elem estructural y
	   sin modificador). */
	Casillero(int pos_x, int pos_y);

	/* Get Pos X: Devuelve la posicion x del casillero. */
	int get_pos_x();

	/* Get Pos Y: Devuelve la posicion y del casillero. */
	int get_pos_y();
	
	/* Get Estructural: Devuelve una referencia al elemento estructural del casillero. Si no posee devuelve NULL. */
	S_ptr<Elemento> get_estructural();
	
	/* Get Modificador: Devuelve una referencia al elemento modificador del casillero. Si no posee devuelve NULL. */
	S_ptr<Elemento> get_modificador();

	/* Tiene Modificador: Devuelve true si el casillero tiene un modificador, false en caso contrario. */
	bool tiene_modificador();

	/* Agregar Elemento: Recibe un elemento por parametro e intenta agregarlo al casillero. Si el elemento es
	   un estructural lo agrega como estructural y sino lo agrega como modificador. Si no puede agregarlo devuelve
	   false, de lo contrario devuelve true. */
	bool agregar_elemento(S_ptr<Elemento> elemento);

	/* Remover Modificador: Remueve el modificador del casillero si este posee uno. Si pudo eliminar devuelve
	   true, sino devuelve false. */
	bool remover_modificador();

	/* Remover Estructural: Remueve el elemento estructural del casillero, si este posee uno. Si tiene un modificador
	   primero remueve ese y luego el estructural.
	   Si pudo eliminar devuelve true, sino devuelve false. */
	bool remover_estructural();

	/* //////////TEMPORAL////////// */
	void imprimir();
	
};

#endif
