#ifndef __MUNDO_H__
#define __MUNDO_H__

/**
*	@brief	Define una interfaz para todos los mundos
*/

#include <server/MapaBajoNivel.h>

class MundoBajoNivel
{
	public:	
		/**
		*	@brief	Debe devolver el mundo que se encuentra actualmente activo, 
		*			es decir el que se esta jugando	
		*
		*	@return	Objeto del tipo MapaBajoNivel que es el mapa activo
		*/
		virtual S_ptr<MapaBajoNivel> get_mapa_activo() = 0;
	
		/**
		*	@brief 	Destructor de la clase
		*/
		virtual ~MundoBajoNivel(){}
		
		/**
		*	@brief	Debe permitir agregar un mapa.
		*
		*	@param	Smart pointer con el mapa a agregar
		*/		
		virtual void agregar_mapa(S_ptr<MapaBajoNivel> mapa)=0;
		
		/**
		*	@brief 	Debe retornar la cantidad de niveles del mapa
		*	
		*	@return cantidad de niveles del mapa
		*/
		virtual int cantidad_niveles()= 0;
			
		/**
		*
		*	@brief  Debe implementar las operaciones que se realizan al
		*			avanzar de nivel
		*/
		virtual void pasar_de_nivel()=0;
};

#endif /* __MUNDO_H__ */
