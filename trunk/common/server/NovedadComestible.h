#ifndef __NOVEDADCOMESTIBLE_H__
#define __NOVEDADCOMESTIBLE_H__

#include <common/smart_pointer.h>
#include <server/Comestible.h>

class NovedadComestible{
	private:
		bool _aparece;
		S_ptr<Comestible> comestible;
	public:
		NovedadComestible(const NovedadComestible& NC);
		NovedadComestible(S_ptr<Comestible> comestible,bool aparece);

		S_ptr<Comestible> get_comestible();

		bool aparece();
	
};

#endif /* __NOVEDADCOMESTIBLE_H__ */
