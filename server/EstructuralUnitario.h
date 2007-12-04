#ifndef __ESTRUCTURAL_H__
#define __ESTRUCTURAL_H__

/**
*	@brief	Esta clase implementa cada una de las unidades basicas que posee un
*			estructural complejo, como sea una cruz o un pasillo (comp por 3 unidades)
*/

#include "Comestible.h"
#include "../common/smart_pointer.h"
#include "Jugador.h"
#include "Direccion.h"

//definiciones

#define _CASA_FANTASMA		1	
//no esta especificado en el enunciado, tomo uno cualquiera que no genere problemas
#define _PASILLO			-1	
#define _SALIDA_PACMAN		0

class EstructuralUnitario{
		
	private:
	
		EstructuralUnitario(EstructuralUnitario &c);
		
		//conecciones en las cuatro direcciones
		S_ptr<EstructuralUnitario> arriba;
		S_ptr<EstructuralUnitario> abajo;
		S_ptr<EstructuralUnitario> derecha;
		S_ptr<EstructuralUnitario> izquierda;
	
		//posicion en el mapa
		Posicion posicion;
	
		void set_posicion(Posicion &p);
	
	public:
		
		//define los tipos de estructurales
		typedef const char Enum_Estructural;
		
		static Enum_Estructural Casa_Fanstasma;
		static Enum_Estructural Pasillo;
		static Enum_Estructural Salida_Pacman;	
		
		/**
		*	@brief	Constructor de la clase
		*
		*	@param 	Posicion del estructural
		*/
		EstructuralUnitario(Posicion &p);	
		
		/**
		*	@brief 	Destructor de la clase
		*/
		virtual ~EstructuralUnitario();
		
		/**
		*	@brief	Declara un metodo abstracto el cual debe encargarse de 
		*			realizar las operaciones necesarias cuando un jugador
		*			ingresa al estructural
		*
		*	@param 	jugador Jugador que ingresa al estructural
		*/
		virtual void ingresar(Jugador& jugador) = 0;
		
		/**
		*	@brief  Declara un metodo abstracto que debe devovler el tipo de
		*			estructural al cual corresponde. Los hijos deben implementarlo
		*			utilizando los tipos definidos en esta clase
		*
		*	@return Tipo del estructural
		*/
		virtual EstructuralUnitario::Enum_Estructural get_tipo()=0;
	
		/**
		*	@brief 	Devuelve la comida que posee el estructural
		*
		*	@return Por defecto devuelve un smart_pointer nulo
		*/
		virtual S_ptr<Comestible> get_comida();
		
		/**
		*	@brief	Setters de los vecinos en las diferentes direcciones
		*
		*	@param 	Smart_pointer con el vecino que se desee
		*/
		void set_arriba(S_ptr<EstructuralUnitario> e);
		void set_abajo(S_ptr<EstructuralUnitario> e);
		void set_derecha(S_ptr<EstructuralUnitario> e);
		void set_izquierda(S_ptr<EstructuralUnitario> e);
		
		/**
		*	@brief	Getters de los vecinios
		*
		*	@return	Smart_pointer con el vecino
		*/
		S_ptr<EstructuralUnitario> get_arriba();
		S_ptr<EstructuralUnitario> get_abajo();
		S_ptr<EstructuralUnitario> get_derecha();
		S_ptr<EstructuralUnitario> get_izquierda();
		
		/**
		*	@brief	Este metodo retorna un vecino a partir de una direccion dada
		*
		*	@param 	dir Direccion en la cual se quiere el vecino
		*
		*	@return Vecino en esa direccion. SI no tiene devuelve smart_pointer 
		*			nulo.		
		*/
		S_ptr<EstructuralUnitario> get_vecino(Direccion &dir);
		
		/**
		*	@brief	Permite obtener la posicion del estructural
		*
		*	@return Posicion del estructural
		*/		
		Posicion& get_posicion();
		
		/**
		*	@brief  Permite evaluar para saber si es salida de pacman o no
		*
		*	@return Por defecto devuelve false, si se desea, los hijos la pueden
		*			redefnir
		*/
		virtual bool es_salida_pacman();
		
		/**
		*	@brief  Permite evaluar para saber si es casa de fantasmas o no
		*
		*	@return Por defecto devuelve false, si se desea, los hijos la pueden
		*			redefnir
		*/
		virtual bool es_casa_fantasma();
		
		/**
		*	@brief	Permite saber si este estructural esta conectado a otro
		*
		*	@param  Estructural con el que se quiere conectar
		*
		*	@return true si estan conectados, false en caso contrario
		*/
		bool tiene_conexion(S_ptr<EstructuralUnitario> e);
	
};
#endif /*__ESTRUCTURAL_H__*/
