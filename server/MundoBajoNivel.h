#ifndef __MUNDO_H__
#define __MUNDO_H__

/**
*	@brief	Define una interfaz para todos los mundos
*/

#include "MapaBajoNivel.h"

class MundoBajoNivel
{
	public:	
		/**
		*	@brief	Debe devolver el mundo que se encuentra actualmente activo, 
		*			es decir el que se esta jugando	
		*
		*	@return	Objeto del tipo MapaBajoNivel que es el mapa activo
		*/
		virtual MapaBajoNivel& get_mapa_activo() = 0;
	
		/**
		*	@brief 	Destructor de la clase
		*/
		virtual ~MundoBajoNivel(){}
		
<<<<<<< .mine
		/**
		*	@brief	Debe permitir agregar un mapa.
		*
=======
>>>>>>> .r249
		*	@param	Smart pointer con el mapa a agregar
		*/		
		virtual void agregar_mapa(S_ptr<MapaBajoNivel> mapa)=0;
		
		/**
		*	@brief 	Debe retornar la cantidad de niveles del mapa
		*	
		*	@return cantidad de niveles del mapa
		*/
		virtual int cantidad_niveles()= 0;
};

#endif /* __MUNDO_H__ */
