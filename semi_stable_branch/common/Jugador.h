#ifndef __JUGADOR_H__
#define __JUGADOR_H__

#include "../common/smart_pointer.h"
#include "Personaje.h"
#include "Posicion.h"
#include "Direccion.h"
#include "Comestible.h"

/** @brief Clase que representa al jugador.
 *
 *  Este tiene un personaje, que es el que define el comportamiento del mismo
 *
 */

typedef Personaje * Tipo_Personaje;

class Jugador{
	
	private:
		unsigned int id;
		Tipo_Personaje personaje;
		Posicion posicion;
		Direccion  * dir;	
		int puntos;
		bool invalido;
		
	public:
		/** @brief Constructor de la clase.
		 *
		 *  @param id  Identificador numerico del jugador.
		 *  @param personaje Un tipo personaje correspondiente al jugador
		 */
		Jugador(int id, Tipo_Personaje personaje);

		/** @brief Constructor de la clase.
		 *
		 *  @param id  Identificador numerico del jugador.
		 */
		Jugador(unsigned int id);
		
		/**
		 *	@brief Destructor de la clase
		 */
		~Jugador();
			
		/** @brief 	Devuelve el personaje del jugador.
		 *
		 *  @return El personaje del jugador.
		 */
		Tipo_Personaje get_personaje();
		
		/**
		 *	@brief	Devuelve el id del jugador
		 *
		 *	@return El id del jugador
		 */
		unsigned int get_id();
			
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
		
		/**
		*	@brief	Asigna la direccion al jugador
		*
		*	@param dir direccion a asignar
		*/
		void set_direccion(Direccion *dir);		
		
		/** @brief Implementa un metodo de acceso para que el jugador coma
		 *	   la comida que hay en el mapa.
		 *
		 *	@param comestible Puntero que referencia al comestible a comer
		 */
		bool comer(Comestible& comestible);
		
		/**
		 *	@brief 	Permite evaluar si colisiono con otro jugador, para esto,
		 *			utiliza el metodo respectivo de su personaje
		 *
		 *	@param	Jugador con el que colisiono
		 */
		void colisiono(Jugador* jugador);
		
		/**
		*	@brief 	Incrementa la cantidad de puntos que posee el jugador
		*
		*	@param 	cant Cantidad de puntos que se deben incrementar
		*/
		void incrementar_puntos(int cant);
		
		/**
		*	@brief	Permite obtener la cantidad de puntos que posee el jugador
		*
		*	@return La cantidad de puntos que posee el jugador
		*/
		int get_puntos();
		
		void set_puntos(int puntos);

		/**
		*	@brief	Permite saber si el jugador es invalido o no
		*
		*	@return true si es invalido, false en caso contrario
		*/
		bool es_invalido();
		

		/**
		*	@brief	Permite quitarle el personaje al jugador liberando la memoria
		*/
      		void quitar_personaje();

};

#endif /*__JUGADOR_H__*/
