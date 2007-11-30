#ifndef __MUNDOBASICIMP_H__
#define __MUNDOBASICIMP_H__

#include <list>
#include "Mundo.h"
#include "MapaBajoNivel.h"
#include "../common/smart_pointer.h"
#include <string>

class MundoBasicImp : public Mundo
{
	public:
	//private:
		MundoBasicImp(std::string ruta_mundo);
		~MundoBasicImp();

		//static S_ptr<Mundo> instancia;
	
	//public:
		//static S_ptr<Mundo> get_instancia();
		
	private:
		std::list<S_ptr<MapaBajoNivel> > mapas;

	public:
		MapaBajoNivel& get_mapa_activo();
};

#endif /* __MUNDOBASICIMP_H__ */
