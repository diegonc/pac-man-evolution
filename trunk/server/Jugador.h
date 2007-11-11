#ifndef __JUGADOR_H__
#define __JUGADOR_H__

#include "smart_pointer.h"

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
	
	public:
		/** @brief Constructor de la clase.
		 *
		 *  @param id  Identificador numerico del jugador.
		 *  @param personaje Un tipo personaje correspondiente al jugador
		 */
	
		Jugador(int id, Tipo_Personaje personaje ) : id(id), personaje(personaje){}
		
		/** @brief Devuelve el personaje del jugador.
		 *
		 *  @return id  El personaje del jugador.
		 */
		Tipo_Personaje get_personaje();
			
		/** @brief Asigna un personaje nuevo al jugador.
		 *
		 *  @param id  Personaje que se desee asignar.
		 */
		void set_personaje(Tipo_Personaje personaje);
	
	
};

#endif /*__JUGADOR_H__*/
