#ifndef __JUGADOR_H__
#define __JUGADOR_H__

/****************************************************************************

 i m   m pppp oooo rrrr ttttt aaaa n  n ttttt eeee  !!!!!   
 i mm mm p  p o  o r  r   t   a  a nn n   t   e     !!!!!
 i m m m pppp o  o rrrr   t   aaaa n nn   t   ee     !!! 
 i m   m p    oooo r r    t   a  a n  n   t   eeee    0  
	
No se si sigue teniendo sentido esta clase, podemos pasar todo esto a cliente

y listo.........

******************************************************************************/
#include "../common/smart_pointer.h"
#include "Personaje.h"

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
