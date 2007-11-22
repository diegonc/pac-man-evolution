#ifndef __JUGADOR_H__
#define __JUGADOR_H__

#include "../common/smart_pointer.h"
#include "Personaje.h"
#include "Posicion.h"
#include "Direccion.h"
#include "Operacion.h"

/** @brief Clase que representa al jugador.
 *
 *  Este tiene un personaje, que es el que define el comportamiento del mismo
 *
 */

class Jugador{
	typedef S_ptr<Personaje> Tipo_Personaje;
	
	private:
		int id;
		Tipo_Personaje personaje;
		Posicion posicion;
		Direccion dir;	
		
	public:
		/** @brief Constructor de la clase.
		 *
		 *  @param id  Identificador numerico del jugador.
		 *  @param personaje Un tipo personaje correspondiente al jugador
		 */
		Jugador(int id, Tipo_Personaje personaje) :
			id(id),
			personaje(personaje),
			dir( Direccion::Norte ) /* Arrancan pa'l norte. */
		{}

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
		Direccion get_direccion() { return dir; }
		
		/** @brief Devuelve el personaje del jugador.
		 *
		 *  @param operacion Operacion que debe realizar el jugador
		 */
		void ejecutar_operacion(Operacion& operacion);
};

#endif /*__JUGADOR_H__*/
