#ifndef __NOVEDADCOMESTIBLE_H__
#define __NOVEDADCOMESTIBLE_H__

#include "Comestible.h"

class NovedadComestible{
	private:
		bool _aparece;
		Comestible * comestible;
	public:
		NovedadComestible(const NovedadComestible& NC);
		NovedadComestible(Comestible * comestible,bool aparece);

		Comestible * get_comestible();

		bool aparece();
	
};

#endif /* __NOVEDADCOMESTIBLE_H__ */
