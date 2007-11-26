#ifndef __JUGADOR_H__
#define __JUGADOR_H__

#include "../common/smart_pointer.h"
#include "Personaje.h"
#include "Posicion.h"
#include "Direccion.h"
#include "Operacion.h"
#include "Comestible.h"

/** @brief Clase que representa al jugador.
 *
 *  Este tiene un personaje, que es el que define el comportamiento del mismo
 *
 */

typedef S_ptr<Personaje> Tipo_Personaje;

class Jugador{
	
	private:
		int id;
		Tipo_Personaje personaje;
		Posicion posicion;
		Direccion  * dir;	
		int puntos;
		
	public:
		/** @brief Constructor de la clase.
		 *
		 *  @param id  Identificador numerico del jugador.
		 *  @param personaje Un tipo personaje correspondiente al jugador
		 */
		Jugador(int id, Tipo_Personaje personaje);

		~Jugador() {}
			
		/** @brief Devuelve el personaje del jugador.
		 *
		 *  @return El personaje del jugador.
		 */
		Tipo_Personaje get_personaje();
			
		/** @brief Asigna un personaje nuevo al jugador.
		 *
		 *  @param personaje Personaje que se desee asignar.
		 */
		void set_personaje(Tipo_Personaje personaje);
		
		/** @brief Asigna una posicion nueva al jugador
		 *
		 *  @param pos_nueva Posicion nueva a settear
		 */
		void set_posicion(Posicion &pos_nueva);
			
		/** @brief Devuelve la posicion del jugador.
		 *
		 *  @return La posicion del jugador
		 */
		Posicion& get_posicion();
		
		/** @brief Devuelve el personaje del jugador.
		 *
		 *  @return id  El personaje del jugador.
		 */
		Direccion& get_direccion();
		
		/** @brief Devuelve el personaje del jugador.
		 *
		 *  @param operacion Operacion que debe realizar el jugador
		 */
		void ejecutar_operacion(Operacion& operacion);
		
		/** @brief Implementa un metodo de acceso para que el jugador coma
		 *	   la comida que hay en el mapa.
		 *
		 *	@param comestible Puntero que referencia al comestible a comer
		 */
		void comer(Comestible& comestible);
		
		void incrementar_puntos(int cant);
		
		int get_puntos();
};

#endif /*__JUGADOR_H__*/
