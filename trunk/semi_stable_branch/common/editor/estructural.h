//Header
#ifndef Estructural_h_
#define Estructural_h_

//Incluyo las librerias necesarias
#include "elemento.h"
#include "componente.h"
#include "punto.h"

/* CLASE ESTRUCTURAL: Esta clase abstracta representa un elemento estructural y desciende de elemento.
   El elemento estructural esta conformado por una matriz de componentes internas. */

class Estructural : public Elemento {

	private:
		S_ptr<Componente>** componentes; //Matriz de componentes

	protected:

	/* Constructor: Inicializa el elemento con los datos pasados por parametro. */
	Estructural(int pos_x, int pos_y, int ancho, int alto, Orientacion orientacion);

	/* Set Habitable: Asigna el estado del componente en las posiciones x, y, relativas al elemento
	   (habitable o no) */
	void set_habitable (int pos_x, int pos_y, bool habitable);

	/* Set Posible Conexion: Asigna en (x,y) relativas al elemento, una posible conexion, convirtiendo
	   a la componente en ese punto, en un pto de conexion. */
	void set_posible_conexion (int pos_x, int pos_y, S_ptr<Punto> posib_conex);

	public:

	/* Destructor: Libera los recursos consumidos por el elemento. */
	virtual ~Estructural();

	/* Es Estructural: Devuelve true porque el elemento es estructural. */
	virtual bool es_estructural();

	/* Es Punto Conexion: Dadas unas coordenadas x,y devuelve true si las mismas son un punto de conexion del
	  elemento o false en caso contrario */
	virtual bool es_punto_conexion(int x, int y);
	
	/* Get Posible Conexion: Devuelve un punto con la posible conexion del elemento. Si no es un pto de conexion
	   del elemento devuelve un punto nulo. */
	virtual S_ptr<Punto> get_posible_conexion(int x, int y);
	
	/* Hay Conexion: Dadas (x1,y1) pertenecientes al elemento, y (x2,y2) devuelve true si: 
	   - Hay conexion en (x1,xy) con un casillero vacio en (x2,y2).
	   - (x1,y1) y (x2,y2) pertencen al elementos.
	   - Hay conexion mutua entre (x1,y1) pertenciente al elemento y (x2,y2) perteneciente a otro elem. 
	   En cualquier otro caso devuelve false. */
	virtual bool hay_conexion(int x1, int y1, int x2, int y2, Mapa* mapa);

	/* Es Habitable: Dadas unas coordenadas x,y devuelve true si las mismas son habitables por un personaje o
	   modificador y false en caso contrario */
	virtual bool es_habitable(int x, int y);

	/* Agregate: Dado el mapa pasado por parametro, el elemento verifica si puede insertarse en mismo,en 
	   la posicion con la que fue creado. Si puede, se agrega y se conecta con todos los vecinos (si es estruct).
	   Devuelve true si se pudo agregar, false en caso contrario. */
	virtual bool agregate(S_ptr<Elemento> instancia, Mapa* mapa);
		
	/* Quitate: Dado el mapa pasado por parametro, el elemento se encarga de removerse del mismo. */
	virtual void quitate(S_ptr<Elemento> instancia, Mapa* mapa);

	protected:

	/* Conectar: Se encarga de recorrer todos los componentes y por cada pto de conexion, obtener la posible
	   conexion e intentar conectarse. Si no puede realizar alguna de las conexiones devuelve false, sino
	   devuelve true. */
	virtual bool conectar(S_ptr<Elemento> instancia, Mapa* mapa);
	
};

#endif
