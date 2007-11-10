#ifndef __MUNDOMOCKIMPL_H__
#define __MUNDOMOCKIMPL_H__

#include <list>
#include "Mundo.h"
#include "Mapa.h"

class MundoMockImpl : public Mundo
{
	private:
		MundoMockImpl();
		~MundoMockImpl();

		static Mundo* instance;

	public:
		static MundoMockImpl& get_instance();
		static void destroy();
		
	private:
		std::list<Mapa*> mapas;
		std::list<Mapa*>::iterator cursor;
		
		Mapa* get_mapa_activo();
};

#endif /* __MUNDOMOCKIMPL_H__ */
 