#include "ComestibleFactory.h"
#include "PowerUp.h"
#include "Frutita.h"
#include "Quesito.h"


ComestibleFactory::ComestibleFactory(ComestibleFactory &c){}

ComestibleFactory::ComestibleFactory(){}
	
ComestibleFactory::~ComestibleFactory(){}

Comestible * ComestibleFactory::construir(Comestible::Enum_Comestible tipo, Posicion &p){
	
	switch(tipo){
		case 0:	return new PowerUp(p);
				break;
		case 1:	return new Quesito(p);
				break;
		case 2:	return new Frutita(p);
				break;
		default://TODO tirar excepcion?
				return 0;
	}

}
