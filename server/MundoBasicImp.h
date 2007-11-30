#ifndef __MUNDOBASICIMP_H__
#define __MUNDOBASICIMP_H__

#include <list>
#include "MundoBajoNivel.h"
#include "MapaBajoNivel.h"
#include "../common/smart_pointer.h"
#include <string>

class MundoBasicImp : public MundoBajoNivel
{
	private:
		std::list<S_ptr<MapaBajoNivel> > mapas;
		int cant_niveles;

	public:
		MundoBasicImp(std::string ruta_mundo);
		
		~MundoBasicImp();
	
		MapaBajoNivel& get_mapa_activo();
	
		void agregar_mapa(S_ptr<MapaBajoNivel> mapa);
	
		int cantidad_niveles();
};

#endif /* __MUNDOBASICIMP_H__ */
