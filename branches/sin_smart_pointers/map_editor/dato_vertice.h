//Header
#ifndef Dato_Vertice_h_
#define Dato_Vertice_h_

//Incluyo las librerias necesarias
#include "elemento.h"
#include "../common/smart_pointer.h"

using namespace std;

class Elemento;

/* CLASE DATO VERTICE: Clase que representa el contenido de un vertice para el grafo que controla
   las conexiones de elementos. */

class DatoVertice {

	//Atributos
	private:
		S_ptr<Elemento> elem; //Elemento contenido en el vertice
		bool marcado; //Booleano que controla si el vertice esta o no marcado (para recorridos)

	public:

	/* Constructor: Inicializa el dato del vertice con el elemento pasado por parametro. */
	DatoVertice(S_ptr<Elemento> elem);

	/* Get Elemento: Devuelve el elemento contenido en un dato vertice. */
	S_ptr<Elemento> get_elemento();
	
	/* Marcar: Marca el dato vertice. */
	void marcar();
	
	/* Desmarcar: Desmarca el dato vertice. */
	void desmarcar();
	
	/* Esta Marcado: Devuelve true si el vertice esta marcado, false en caso contrario. */
	bool esta_marcado();
	
	//operadores de comparacion

	friend bool operator==(DatoVertice &dato1, DatoVertice &dato2){
		return (dato1.get_elemento() == dato2.get_elemento());
	}

	friend bool operator!=(DatoVertice &dato1, DatoVertice &dato2){
		return (dato1.get_elemento() != dato2.get_elemento());
	}

};

#endif
