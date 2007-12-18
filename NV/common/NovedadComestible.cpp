#include "NovedadComestible.h"

NovedadComestible::NovedadComestible(const NovedadComestible& NC){
	this->_aparece=NC._aparece;
	this->comestible=NC.comestible;
}

NovedadComestible::NovedadComestible(Comestible * comestible,bool aparece){
	this->comestible=comestible;
	this->_aparece=aparece;
}

Comestible * NovedadComestible::get_comestible(){
	return comestible;
}

bool NovedadComestible::aparece(){
	return _aparece;
}
