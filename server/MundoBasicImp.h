#ifndef __MUNDOBASICIMP_H__
#define __MUNDOBASICIMP_H__

#include "Mundo.h"
#include "Mapa.h"

class MundoBasicImp : public Mundo
{
	private:
		MundoBasicImp();
		~MundoBasicImp();

		static MundoBasicImp* instance;
	
	public:
		static Mundo& get_instance();
		static void destroy();
	
	public:
		Mapa& get_mapa_activo();
};

#endif /* __MUNDOBASICIMP_H__ */
