#ifndef __MUNDOBASICIMP_H__
#define __MUNDOBASICIMP_H__

/**
*	@brief Implementacion basica del mundo
*/

#include <list>
#include <server/MundoBajoNivel.h>
#include <server/MapaBajoNivel.h>
#include <common/smart_pointer.h>
#include <string>

class MundoBasicImp : public MundoBajoNivel
{
	private:
		std::list<MapaBajoNivel*  > mapas;
		int cant_niveles;

	public:
		/**
		*	@brief Constructor
		*/
		MundoBasicImp();
			
		/**
		*	@brief Destructor
		*/
		~MundoBasicImp();
	
		/**
		*	@brief Implementacion del metodo de la interfaz mundo
		*/
		MapaBajoNivel* get_mapa_activo();
	
		/**
		*	@brief Implementacion del metodo de la interfaz mundo
		*/
		void agregar_mapa(MapaBajoNivel* mapa);
	
		/**
		*	@brief Implementacion del metodo de la interfaz mundo
		*/
		int cantidad_niveles();
		
		/**
		*	@brief Implementacion del metodo de la interfaz mundo
		*/
		void pasar_de_nivel();
};

#endif /* __MUNDOBASICIMP_H__ */
