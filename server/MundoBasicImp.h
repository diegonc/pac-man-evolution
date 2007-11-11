#ifndef __MUNDOBASICIMP_H__
#define __MUNDOBASICIMP_H__

#include <list>
#include "Mundo.h"
#include "Mapa.h"
#include "../common/smart_pointer.h"

class MundoBasicImp : public Mundo
{
	private:
		MundoBasicImp();
		~MundoBasicImp();

		static S_ptr<Mundo> instancia;
	
	public:
		static S_ptr<Mundo> get_instancia();
		
	private:
		std::list<Mapa*> mapas;

	public:
		Mapa& get_mapa_activo();
};

#endif /* __MUNDOBASICIMP_H__ */
