//Header
#ifndef Componente_h_
#define Componente_h_

#include <editor/punto.h>
#include <common/smart_pointer.h>

/* CLASE COMPONENTE: Representa un pedazo de elemento estructural que puede ser habitable o punto de conexion
   del elemento. */

class Componente {

	private:

	  bool habitable; //Indica si la componente es habitable
	  S_ptr<Punto> posib_conexion; //Coordenadas con las cuales establecer una posible conexion

	public:

	  /* Constructor: Inicializa a la componente como habitable y sin posible conexion */
	  Componente();

	  /* Set Habitable: Asigna el estado del componente (habitable o no) */
	  void set_habitable (bool habitable);

	  /* Set Posible Conexion: Asigna al componente una coordenada de una posible conexion, con lo cual
	     la componente se hace pto de conexion. */
	  void set_posible_conexion (S_ptr<Punto> pto_conexion);

	  /* Es Habitable: Devuelve true si el componente es habitable, false en caso contrario */
	  bool es_habitable();

	  /* Es Pto Conexion: Devuelve true si el componente es un pto de conexion del elemento que lo contiene,
	     false en caso contrario. */
	  bool es_pto_conexion();

	  /* Get Posible Conexion: Devuelve un punto con la posible conexion del componente. Si no es un pto de conexion
	     del elemento devuelve NULL. */
	  S_ptr<Punto> get_posible_conexion();

};

#endif
