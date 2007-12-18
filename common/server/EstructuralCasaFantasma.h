#ifndef __CASILLERO_CASA_FANSTASMA_H__
#define __CASILLERO_CASA_FANSTASMA_H__

/**
*	@brief	Esta clase representa un Estructural para casa de fantasma. Es
*			un estructural unitario, con la particularidad de que no contiene
*			comestible, es desde donde parten los fantasmas y permite que estos
*			revivan
*/

#include <server/EstructuralUnitario.h>

class EstructuralCasaFantasma : public EstructuralUnitario{
	
	private:
		EstructuralCasaFantasma(EstructuralCasaFantasma &e);
	
	public:
		/**
		*	@brief	Constructor de la clase
		*
		*	@param	Posicion del estructural
		*/
		EstructuralCasaFantasma(Posicion &p);
		
		/**
		*	@brief	Destructor de la clase
		*/
		~EstructuralCasaFantasma();
	
		/**
		*	@brief 	Implementacion del metodo de la clase estructural
		*
		*	@param	jugador Jugador que ingresa al estructural
		*/
		void ingresar(Jugador& jugador);
		
		/**
		*	@brief	Devuelve el tipo de estructural definido en EstructuralUnitario
		*
		*	@return Tipo del cual es el estructural
		*/
		EstructuralUnitario::Enum_Estructural get_tipo();
	
		/**
		*	@brief Redefinicion del metodo es_casa_fantasma() de EstructuralUnitario
		*
		*	@return true
		*/
		bool es_casa_fantasma();
};

#endif /*__CASILLERO_CASA_FANSTASMA_H__*/
