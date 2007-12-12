//Header
#ifndef Elemento_h_
#define Elemento_h_

//Incluyo las librerias necesarias
#include "mapa.h"
#include "definiciones.h"
#include "../common/smart_pointer.h"
#include "../common/grafo.h"
#include "../common/vertice.h"
#include "../common/arco.h"

class Mapa;

using namespace std;

/* CLASE ELEMENTO: Esta clase abstracta representa un elemento, ya sea estructural o modificador. El elemento
   contiene una coordenada de su vertice superior izq, un ancho y un alto, y proporciona metodos para
   agregarse a un mapa de un nivel determinado, realizando las validaciones pertinentes.
   Tambien contiene una orientacion. */

class Elemento {

	//Atributos
	private:
		int pos_x;
		int pos_y;
		int ancho;
		int alto;
		Orientacion orientacion;

	protected:

	/* Constructor: Inicializa el elemento con los datos pasados por parametro. */
	Elemento(int pos_x, int pos_y, int ancho, int alto, Orientacion orientacion);

	public:

	/* Destructor: Libera los recursos consumidos por el elemento. */
	virtual ~Elemento(){}

	/* Get Pos X: Devuelve la posicion x del elemento. */
	int get_pos_x();

	/* Get Pos Y: Devuelve la posicion y del elemento. */
	int get_pos_y();
	
	/* Get Ancho: Devuelve el ancho en unidades del elemento. */
	int get_ancho();
	
	/* Get Alto: Devuelve el alto en unidades del elemento. */
	int get_alto();

	/* Get Orientacion: Devuelve la orientacion del elemento */
	Orientacion get_orientacion();
		
	/* Get Tipo: Devuelve el tipo del elemento */
	virtual TipoElem get_tipo() = 0;
	
	/* Es Punto Conexion: Dadas unas coordenadas x,y devuelve true si las mismas son un punto de conexion del
	  elemento o false en caso contrario */
	virtual bool es_punto_conexion(int x, int y) = 0;
		
	/* Hay Conexion: Dadas (x1,y1) y (x2,y2) devuelve true si hay conexion, false en caso contrario. */
	virtual bool hay_conexion(int x1, int y1, int x2, int y2) = 0;

	/* Es Habitable: Dadas unas coordenadas x,y devuelve true si las mismas son habitables por un personaje o
	   modificador y false en caso contrario */
	virtual bool es_habitable(int x, int y) = 0;

	/* Agregate: Dado el mapa pasado por parametro, el elemento verifica si puede insertarse en mismo,en 
	   la posicion con la que fue creado. Si puede, se agrega y se conecta con todos los vecinos (si es estruct).
	   Devuelve true si se pudo agregar, false en caso contrario. */
	virtual bool agregate(S_ptr<Elemento> instancia, Mapa* mapa) = 0;

	/* Quitate: Dado el mapa pasado por parametro, el elemento se encarga de removerse del mismo. */
	virtual void quitate(S_ptr<Elemento> instancia, Mapa* mapa);

	/* Es Estructural: Devuelve true si el elemento es estructural, false en caso contrario */
	virtual bool es_estructural() = 0;
	
	/* Get Ruta Imagen: Devuelve una cadena con la ruta donde se encuentra la imagen que representa al elemento */
	virtual char* get_ruta_imagen() = 0;
	
	//operadores de comparacion
	
	friend bool operator<(Elemento &elem1, Elemento &elem2){
		if (elem1.get_pos_x() < elem2.get_pos_x())
			return true;
		else
			if ((elem1.get_pos_x() == elem2.get_pos_x()) && (elem1.get_pos_y() < elem2.get_pos_y()))
				return true;
			else
				return false;
	}

	/* ///////////////TEMPORAL/////////////// */
	virtual char* toString() = 0;
	
};

#endif
