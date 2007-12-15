#include "NovedadComestible.h"

NovedadComestible::NovedadComestible(S_ptr<Comestible> comestible,bool aparece){
	this->comestible=comestible;
	this->_aparece=aparece;
}

S_ptr<Comestible> NovedadComestible::get_comestible(){
	return comestible;
}

bool NovedadComestible::aparece(){
	return _aparece;
}

