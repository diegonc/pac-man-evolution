#ifndef __COMPARADOR_POSICION_H__
#define __COMPARADOR_POSICION_H__


	
class ComparadorPosicion{
	
	public:
		bool operator()(const MapaImpSet::Elemento &e1, const MapaImpSet::Elemento &e2){
			if(e1.posicion == e2.posicion )
				return true;
			else
				return false;
		}
};

#endif /*__COMPARADOR_POSICION_H__*/
