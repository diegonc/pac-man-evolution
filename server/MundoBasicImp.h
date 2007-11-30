#ifndef __MUNDOBASICIMP_H__
#define __MUNDOBASICIMP_H__

#include <list>
#include "MundoBajoNivel.h"
#include "MapaBajoNivel.h"
#include "../common/smart_pointer.h"
#include <string>

class MundoBasicImp : public MundoBajoNivel
{
	public:
	//private:
		MundoBasicImp(std::string ruta_mundo);
		~MundoBasicImp();

		//static S_ptr<MundoBajoNivel> instancia;
	
	//public:
		//static S_ptr<MundoBajoNivel> get_instancia();
		
	private:
		std::list<S_ptr<MapaBajoNivel> > mapas;

	public:
		MapaBajoNivel& get_mapa_activo();
};

#endif /* __MUNDOBASICIMP_H__ */
