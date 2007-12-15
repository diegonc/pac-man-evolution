#ifndef __NOVEDADCOMESTIBLE_H__
#define __NOVEDADCOMESTIBLE_H__

#include "smart_pointer.h"
#include "Comestible.h"

class NovedadComestible{
	private:
		bool _aparece;
		S_ptr<Comestible> comestible;
	public:
		NovedadComestible(S_ptr<Comestible> comestible,bool aparece);

		S_ptr<Comestible> get_comestible();

		bool aparece();
	
};

#endif /* __NOVEDADCOMESTIBLE_H__ */
