#ifndef __COMESTIBLE_H__
#define __COMESTIBLE_H__

#include "Personaje.h"
#include "Direccion.h"
#include "Posicion.h"

//definiciones
#define _POWER_UP	1
#define	_QUESITO	0
#define _FRUTITA	2

/** @brief Define una interfaz para todos los elementos del mapa que pueden ser
           comidos, por ejemplo, quesitos, power ups, frutitas, etcs.			
*/
class Comestible{
	private: 
		int puntaje;
		Posicion p;
		bool invalido;
		
	protected:
		Comestible(int puntos, Posicion &pos);			
	
	public:
		//definicion de las constantes que se pueden acceder de forma publica
		typedef const char Enum_Comestible;
	
		static Enum_Comestible power_up;
		static Enum_Comestible quesito;
		static Enum_Comestible frutita;
		
		/**
		* @brief Destructor de la clase
		*/	
		virtual ~Comestible();
	
		/**
		* @brief Retorna los puntos que otorga el comestible al ser comido
		*
		* @return La cantidad de puntos
		*/
		int get_puntos();
		
		/**
		* @brief Metodo que realiza las operaciones que afectan al personaje
		*	     luego de que este coma la comida
		*
		* @param personaje Personaje al cual afecta
		*/
		virtual void afectar_personaje(Personaje& personaje)=0;	
	
		/**
		* @brief Devuelve el tipo de comestible del cual es la instancia
		*
		* @return Tipo de comestible
		*/
		virtual Enum_Comestible get_tipo()=0;
		
		/**
		* @brief Devuelve la orientacion del comestible en el mapa
		*
		* @return La orientacion en un objeto Direccion
		*/
		virtual Direccion get_orientacion();
		
		/**
		* @brief Devuelve la posicion del comestible
		*
		* @return Objeto del tipo posicion con los datos del comestible
		*/
		Posicion& get_posicion();
		
		/**
		* @brief Settea como invalido a un comestible
		*/
		 void set_invalido();

		/**
		* @brief Permite saber si es invalido o no
		*
		* @return True en caso positivo, false en caso contrario
		*/
		bool es_invalido();
};


#endif /*__COMESTIBLE_H__*/
