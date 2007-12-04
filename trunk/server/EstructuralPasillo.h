#ifndef __CASILLERO_PASILLO_H__
#define __CASILLERO_PASILLO_H__

/**
*	@brief 	Esta clase es un estructural unitario por el cuar circulan los
*			jugadores. Pueden haber comestibles asi como la salida del pacman.
*/

#include "../common/smart_pointer.h"
#include "Comestible.h"
#include "EstructuralUnitario.h"

class EstructuralPasillo : public EstructuralUnitario{
	private:
		//comida que tiene
		S_ptr<Comestible> comida;
		//variable booleana que le permite setear el modificador de salida pacman
		bool salida;
			
	public:
		/**
		*	@brief Constructor de la clase
		*
		*	@param  tipo Tipo de comestible que contiene
		*	@param	p Posicion del mismo	  
		*/	
		EstructuralPasillo(Comestible::Enum_Comestible &tipo, Posicion &p);
	
		/**
		*	@brief  Constructor de la clase. No le asigna ningun comestible.
		*
		*	@param	p Posicion del mismo	  
		*/	
		EstructuralPasillo(Posicion &p);
		
		/**
		*	@brief	Destructor de la clase
		*/
		~EstructuralPasillo();
	
		/**
		*	@brief 	Implementacion del metodo ingresar de la clase EstructuralUnitario
		*
		*	@param	jugador Jugador que ingresa
		*/
		void ingresar(Jugador& jugador);
	
		/**
		*	@brief	Permite obtener el tipo de estructural
		*
		*	@return Tipo definido en EstructuralUnitario
		*/
		EstructuralUnitario::Enum_Estructural get_tipo();
		
		/**
		*	@brief Permite obtener la comida
		*
		*	@return Un smart pointer con la comida que contiene, en caso de
		*			no poseer ninguna, devuelve un S_ptr nulo, o sea, el 
		*			método .es_nulo() devuelve true
		*/			
		S_ptr<Comestible> get_comida();
	
		/**
		*	@brief 	Permite saber si el pasillo es salida de pacman o no
		*	
		*	@return True si es salida, galse en caso contrario
		*/
		bool es_salida_pacman();
	
		/**
		*	@brief 	Permite settearlo como salida pacman. Luego, es_salida_pacman()
		*		 	retorna true
		*/
		void set_salida_pacman();
	
};

#endif /*__CASILLERO_PASILLO_H__*/
